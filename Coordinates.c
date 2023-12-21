/* COP 3502C Programming Assignment 3
This program is written by: Diyor Suleymanov */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// struct to hold coordinates
typedef struct
{
int x;
int y;
}coords;
// location coordinate
coords L;

// function to find max
int max(int a, int b) {
    return (a > b) ? a : b;
}

//function to read coordinate data
void readData(coords coords[], int n)
{
    int i = 0;

    while (i < n)
    {
        scanf("%d %d", &coords[i].x, &coords[i].y);
        i++;
    }
  }

// function to compare order of coordinates
int compareTo(coords *ptr1, coords *ptr2) {
  //distance formula without squareRoot
    int dist1 = pow(ptr1->x - L.x, 2) + pow(ptr1->y - L.y, 2);
    int dist2 = pow(ptr2->x - L.x, 2) + pow(ptr2->y - L.y, 2);

    if (dist1 < dist2) {
        return -1;
    } else if (dist1 > dist2) {
        return 1;
    } else {
        if (ptr1->x < ptr2->x) {
            return -1;
        } else if (ptr1->x > ptr2->x) {
            return 1;
        } else {
            if (ptr1->y < ptr2->y) {
                return -1;
            } else if (ptr1->y > ptr2->y) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}


//insertsort function
void insertionSort(coords coord[], int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        coords key = coord[i];
        int j = i - 1;

        while (j >= low && compareTo(&key, &coord[j]) < 0)
        {
            coord[j + 1] = coord[j];
            j--;
        }
        coord[j + 1] = key;
    }
}

// merge sort function
void merge(coords coord[], int low, int mid, int high)
{
    int left_size = mid - low + 1, right_size = high - mid;
    coords left[left_size], right[right_size];

    for (int i = 0; i < left_size; i++)
        left[i] = coord[low + i];

    for (int i = 0; i < right_size; i++)
        right[i] = coord[mid + 1 + i];

    int i = 0, j = 0, k = low;
    while (i < left_size && j < right_size)
    {
        if (compareTo(&left[i], &right[j]) <= 0)
            coord[k++] = left[i++];
        else
            coord[k++] = right[j++];
    }
    while (i < left_size)
        coord[k++] = left[i++];

    while (j < right_size)
        coord[k++] = right[j++];
}


// binary search function
int binarySearch(coords coord[], int n, coords key)
{
    int low = 0, high = n, mid;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(coord[mid].x == key.x && coord[mid].y == key.y)
            return mid;
        else if(compareTo(&key, &coord[mid]) < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

 // function to call merge sort
void mergeSort(coords coords[], int low, int high, int t)
{
    int n = high - low + 1;
    int mid = low + (high - low) / 2;

    if (n <= t) //extra test case
    {
        insertionSort(coords, low, high);
        return;
    }

    mergeSort(coords, low, mid - 1, t);
    mergeSort(coords, mid, high, t);
    merge(coords, low, mid - 1, high);
}

#include <stdio.h>

int main()
{   //create and scan first line or input
    int n, s, i, t;
    scanf("%d %d %d %d %d", &n, &s, &L.x, &L.y,  &t);

    coords coord[n];
  //read the coordinates of the data
    readData(coord, n);


    int low = 0, high = n-1;
// threshold determination
    if (t <= 13) {
        insertionSort(coord, 0, n-1);
    } else {
        mergeSort(coord, 0, n-1, t);
    }

    FILE *fp = fopen("out.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int m = high - low + 1;

    for(i=0;i<m;i++)
    {
        printf("%d %d\n", coord[i].x, coord[i].y);
        fprintf(fp, "%d %d\n", coord[i].x, coord[i].y);
    }
// locate and print Query points
    coords key;
    for(i=0;i<s;i++)
    {
        scanf("%d %d", &key.x, &key.y);
        int pos = binarySearch(coord, high, key);
        if(pos != -1) {
            printf("%d %d found at position %d\n", key.x, key.y, pos+low+1);
            fprintf(fp, "%d %d found at position %d\n", key.x, key.y, pos+low+1);
        } else {
            printf("%d %d not found\n", key.x, key.y);
            fprintf(fp, "%d %d not found\n", key.x, key.y);
        }
    }

    fclose(fp);
    return 0;
}


