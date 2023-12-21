#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

typedef struct monster {
  char *name;
  char *element;
  int population;
} monster;

typedef struct region {
  char *name;
  int monster_cnt;
  int total_population;
  monster **monsters;
} region;

typedef struct itinerary {
  int region_cnt;
  region **regions;
  int captures;
} itinerary;

typedef struct trainer {
  char *name;
  itinerary *visits;
} trainer;



monster *makeMonster(char *name, char *element, int population) {

  //create monster struct DMA
  monster *Monsters = malloc(sizeof(monster));

  //copy name and element to array
  Monsters->name = malloc(51 * sizeof(char));
  strcpy(Monsters->name, name);

  Monsters->element = malloc(51 * sizeof(char));
  strcpy(Monsters->element, element);
  //assign population
  Monsters->population = population;

  return Monsters;
}

monster **readMonsters(int *monsterCount) {
  //create variable and Temp DMA
  int Population;
  char *tempName = malloc(sizeof(char) * 51);
  char *tempElement = malloc(sizeof(char) * 51);

// create DMA for monster list
 monster** Mlist = malloc(sizeof(monster*) * *monsterCount);

  for (int i = 0; i < *monsterCount; i++) {

    //loop and scan name element and population
    scanf("%s", tempName);
    scanf("%s", tempElement);
    scanf("%d", &Population);

    // call function within loop
    Mlist[i] = makeMonster(tempName, tempElement, Population);
  }
  // free temp DMA
  free(tempName);
  free(tempElement);
  return Mlist;
}

region **readRegions(int *countRegions, monster **monsterList, int monsterCount) {
  // create Region list and temp DMA for region names
  region **Rlist = malloc(*countRegions * sizeof(region*));
  char *tempName = malloc(51* sizeof(char));

  for (int i = 0; i < *countRegions; i++) {

    Rlist[i] = malloc(monsterCount * sizeof(region *));
    Rlist[i]->name = malloc(51 * sizeof(char));

    scanf("%s", Rlist[i]->name);

    scanf("%d", &Rlist[i]->monster_cnt);

    Rlist[i]->monsters = malloc(Rlist[i]->monster_cnt * sizeof(monster *));


    for (int j = 0; j < Rlist[i]->monster_cnt; j++) {

      scanf("%s", tempName);
      for (int k = 0; k < monsterCount; k++) {
        if (strcmp(tempName, monsterList[k]->name) == 0) {
          Rlist[i]->monsters[j] = monsterList[k];
          Rlist[i]->total_population += monsterList[k]->population;
        }
      }
    }
  }
  free(tempName);
  return Rlist;
}

trainer *loadTrainers(int *trainerCount, region **regionList, int countRegions) {
  // create Trainer array and temporary DMA
  trainer *Tlist = malloc(*trainerCount * sizeof(trainer));
  char *tempRegion = malloc(sizeof(char) * 51);
//first loop to create array for name and visit type itinerary
  for (int i = 0; i < *trainerCount; i++) {
    Tlist[i].name = malloc(51 * sizeof(char));
    Tlist[i].visits = malloc(sizeof(itinerary));

    scanf("%s", Tlist[i].name);

    scanf("%d", &Tlist[i].visits->captures);

    scanf("%d", &Tlist[i].visits->region_cnt);
// create pointer to regions
    Tlist[i].visits->regions = malloc(Tlist[i].visits->region_cnt * sizeof(region *));
// second loop
    for (int x = 0; x < Tlist[i].visits->region_cnt; x++) {
      scanf("%s", tempRegion);
// third loop used to compare and save names
      for (int y = 0; y < countRegions; y++) {
        if ((strcmp(tempRegion, regionList[y]->name)) == 0) {
          Tlist[i].visits->regions[x] = regionList[y];
        }
      }
    }
  }
  free (tempRegion);
  return Tlist;
}

void processInputs(monster **monsterList, int monsterCount, region **regionList, int regionCount, trainer *trainerList, int trainerCount) {
 // create double varibles and assign to 0
  double div = 0, MonsterCapture = 0;

//first loop
  for (int i = 0; i < trainerCount; i++) {

    printf("%s\n", trainerList[i].name);

    //second loop
    for (int j = 0; j < trainerList[i].visits->region_cnt; j++) {

      printf("%s\n", trainerList[i].visits->regions[j]->name);

      //third loop
      for (int k = 0; k < trainerList[i].visits->regions[j]->monster_cnt; k++) {


//find value of dividing montser population in each region by the total population
        div = ((double)trainerList[i] .visits->regions[j]->monsters[k]->population) /
                  (trainerList[i].visits->regions[j]->total_population);
        // number of captures = to divion varible * the number of captures
        MonsterCapture = (double)(div)*trainerList[i].visits->captures;
       // use fmod to find remainer and round up or down
          if (fmod(MonsterCapture, 1.0) >= 0.5) {
            MonsterCapture = ceil(MonsterCapture);
          } else {
            MonsterCapture = floor(MonsterCapture);
          }
// if value is not 0 print
        if (MonsterCapture != 0) {
          printf("%.0f %s\n", MonsterCapture,
                 trainerList[i].visits->regions[j]->monsters[k]->name);
        }else {
          continue;
        }
      }
    }
    printf("\n");
  }
  }

void releaseMemory(monster **monsterList, int monsterCount, region **regionList,
                   int regionCount, trainer *trainerList, int trainerCount) {
  //free monsters
  for(int i = 0; i < monsterCount; i++){
    free(monsterList[i]->element);
    free(monsterList[i]->name);
    free(monsterList[i]);
  }
 //free regions
  for(int j = 0; j < regionCount; j++){
    free(regionList[j]->name);
    free(regionList[j]->monsters);
    free(regionList[j]);
  }
  //free trainers
  for(int k = 0; k < trainerCount; k++){
    free(trainerList[k].name);
    free(trainerList[k].visits->regions);
    free(trainerList[k].visits);
  }
//free base lists
  free(monsterList);
  free(regionList);
  free(trainerList);


}

int main(void) {
  atexit(report_mem_leak);
  //declare structs and ints
  monster **MonsterList;
  region **RegionList;
  trainer *TrainerList;

  int monsterCount = 0, regionCount = 0, trainerCount = 0;
  // scan and call functions
  scanf("%d", &monsterCount);
  MonsterList = readMonsters(&monsterCount);


  scanf("%d", &regionCount);
  RegionList = readRegions(&regionCount, MonsterList, monsterCount);


  scanf("%d", &trainerCount);
  TrainerList = loadTrainers(&trainerCount, RegionList, regionCount);

  processInputs(MonsterList, monsterCount, RegionList, regionCount, TrainerList, trainerCount);

  releaseMemory(MonsterList, monsterCount, RegionList, regionCount, TrainerList, trainerCount);

  return 0;
}
