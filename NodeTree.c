/* COP 3502C Assignment 4
This program is written by: Diyor Suleymanov */
//#include "leak_detector_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 30

typedef struct itemNode {
    char name[MAXLEN];
    int count;
    struct itemNode *left, *right;
} itemNode;

typedef struct treeNameNode {
    char treeName[MAXLEN];
    struct treeNameNode *left, *right;
    itemNode *theTree;
} treeNameNode;

// Functions to create nodes
treeNameNode *createTreeNameNode(char *treeName) {
    treeNameNode *newNode = (treeNameNode *)malloc(sizeof(treeNameNode));
    strcpy(newNode->treeName, treeName);
    newNode->left = newNode->right = NULL;
    newNode->theTree = NULL;
    return newNode;
}
// Function to check if the tree is balanced or not
bool is_balanced(itemNode *root, int *height, int *left_height, int *right_height) {
    if (root == NULL) {
        *height = -1;
        return true;
    }

  int leftHeight, rightHeight;

  bool leftBalanced = is_balanced(root->left, &leftHeight, left_height, right_height);

  bool rightBalanced = is_balanced(root->right, &rightHeight, left_height, right_height);
    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    *left_height = leftHeight;
    *right_height = rightHeight;


  if (!leftBalanced || !rightBalanced) {
        return false;
    }

  int diff = abs(leftHeight - rightHeight);

  return (diff <= 1);
}


// create each item
itemNode *createItemNode(char *name, int count) {

  itemNode *newNode = (itemNode *)malloc(sizeof(itemNode));
    strcpy(newNode->name, name);
    newNode->count = count;
    newNode->left = newNode->right = NULL;

  return newNode;
}

// Functions to build and search the name tree
treeNameNode *buildNameTree(treeNameNode *root, char *treeName) {

  if (root == NULL) {
        return createTreeNameNode(treeName);
    }

  int cur = strcmp(treeName, root->treeName);

  if (cur < 0) {
        root->left = buildNameTree(root->left, treeName);
    }
  else if (cur > 0) {
        root->right = buildNameTree(root->right, treeName);
    }
    return root;
}
 // Search the name of each node
treeNameNode *searchNameNode(treeNameNode *root, char *treeName) {

  if (root == NULL || strcmp(root->treeName, treeName) == 0) {
        return root;
    }

  if (strcmp(treeName, root->treeName) < 0) {

    return searchNameNode(root->left, treeName);}
  else {

    return searchNameNode(root->right, treeName);
    }
}
 // function uses is_balanced and prints results
void check_balance(treeNameNode *root, char *category) {

  treeNameNode *tree = searchNameNode(root, category);

  if (tree != NULL) {

    int height, left_height, right_height;

    bool balanced = is_balanced(tree->theTree, &height, &left_height, &right_height);

    printf("%s: left height %d, right height %d, difference %d, %s\n",
               category, left_height, right_height, abs(left_height - right_height),

      balanced ? "balanced" : "not balanced"); }

  else {
        printf("%s does not exist\n", category);
    }
}

// Functions to insert and search items in item trees
itemNode *insertItemNode(itemNode *root, char *name, int count) {

  if (root == NULL) {

    return createItemNode(name, count);
    }

  int cmp = strcmp(name, root->name);

  if (cmp < 0) {
        root->left = insertItemNode(root->left, name, count);
    }
  else if (cmp > 0) {
        root->right = insertItemNode(root->right, name, count);
    }
  else {
        root->count += count;
    }

  return root;
}
 // Funciton to search for specific item
itemNode *searchItemNode(itemNode *root, char *name) {

  if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

  if (strcmp(name, root->name) < 0) {
        return searchItemNode(root->left, name);
    }
  else {

    return searchItemNode(root->right, name);
    }
}

// Counts the number of items in the tree that come before the given itemName
int count_before(itemNode *root, char *itemName) {

  if (root == NULL) {
        return 0;
    }

  int cmp = strcmp(itemName, root->name);

  if (cmp <= 0) {

    return count_before(root->left, itemName);
    }
  else {

    return 1 + count_before(root->left, itemName) + count_before(root->right, itemName);
    }
}

// Counts the total number of items in the tree
int count_items(itemNode *root) {

  if (root == NULL) {

    return 0;
    }
    return root->count + count_items(root->left) + count_items(root->right);
}

// Decreases the count of the specified item by the given count value
itemNode *decrease(itemNode *root, char *itemName, int count) {

  if (root == NULL) {
        return NULL;
    }

  int cmp = strcmp(itemName, root->name);

  if (cmp < 0) {
        root->left = decrease(root->left, itemName, count);
    }
  else if (cmp > 0) {
        root->right = decrease(root->right, itemName, count);
    }
  else {
        root->count -= count;

    if (root->count <= 0) {

      if (root->left == NULL) {
                itemNode *rightNode = root->right;
                free(root);

        return rightNode;
            } else if (root->right == NULL) {
                itemNode *leftNode = root->left;
                free(root);

        return leftNode;
            } else {
                // Find the smallest node in the right subtree

        itemNode *smallest = root->right;

        while (smallest->left != NULL) {
                    smallest = smallest->left;
                }
                strcpy(root->name, smallest->name);
                root->count = smallest->count;
                root->right = decrease(root->right, smallest->name, smallest->count);
            }
        }
    }
    return root;
}

// Removes the specified item from the tree
itemNode *remove_item(itemNode *root, char *itemName) {

  return decrease(root, itemName, INT_MAX);
}

// Deletes a treeNameNode with a specified treeName from the tree
treeNameNode *delete_name(treeNameNode *root, char *treeName) {
    if (root == NULL) {
        return NULL;
    }

  int cmp = strcmp(treeName, root->treeName);

  if (cmp < 0) {
        root->left = delete_name(root->left, treeName);
    }
  else if (cmp > 0) {
        root->right = delete_name(root->right, treeName);
    }
  else {

    if (root->left == NULL) {
            treeNameNode *rightNode = root->right;
            free(root);
            return rightNode;
        }
    else if (root->right == NULL) {
            treeNameNode *leftNode = root->left;
            free(root);
            return leftNode;
        }
    else {

      // Find the smallest node in the right subtree
      treeNameNode *smallest = root->right;

      while (smallest->left != NULL) {
                smallest = smallest->left;
            }
            strcpy(root->treeName, smallest->treeName);
            root->theTree = smallest->theTree;
            root->right = delete_name(root->right, smallest->treeName);
        }
    }
    return root;
}

// Prints the names of items in an itemNode tree in an in-order fashion
void print_item_tree(itemNode *root) {

  if (root == NULL) {
        return;
    }
    print_item_tree(root->left);
    printf("%s ", root->name);
    print_item_tree(root->right);
}

// Prints the names of treeNameNode in an in-order fashion
void print_item_names(treeNameNode *root) {
    if (root == NULL) {
        return;
    }
    print_item_names(root->left);
    printf("%s ", root->treeName);
    print_item_names(root->right);
}

// Prints the names of treeNameNode
void print_in_order(treeNameNode *root) {
    print_item_names(root);
    printf("\n\n");
}

// Traverses the treeNameNode tree and prints the itemNode trees associated with each treeNameNode
void traverse_in_traverse(treeNameNode *root) {
    if (root == NULL) {
        return;
    }
    traverse_in_traverse(root->left);
    printf("###%s###\n", root->treeName);
    print_item_tree(root->theTree);
    printf("\n");
    traverse_in_traverse(root->right);
}


// Helper function to free the trees
void freeItemTree(itemNode *root) {
    if (root == NULL) {
        return;
    }
    freeItemTree(root->left);
    freeItemTree(root->right);
    free(root);
}

// Free memory function
void freeTree(treeNameNode *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    freeItemTree(root->theTree);
    free(root);
}

int main() {
  //atexit(report_mem_leak);
  //FILE *file = freopen("out.txt", "w", stdout);

    int num_categories, num_items, num_operations;
    // read input
    scanf("%d %d %d\n", &num_categories, &num_items, &num_operations);

    treeNameNode *root = NULL;
    // Build tree of categories
    char category[MAXLEN];
    for (int i = 0; i < num_categories; i++) {
        scanf("%s", category);
        root = buildNameTree(root, category);
    }

    // Print the categories
    print_item_names(root);
    printf("\n");
    fflush(stdout);

    char item[MAXLEN];
    int value;
    for (int i = 0; i < num_items; i++) {
        scanf("%s %s %d", category, item, &value);
        treeNameNode *tree = searchNameNode(root, category);
        if (tree != NULL) {
            tree->theTree = insertItemNode(tree->theTree, item, value);
        }
    }
    traverse_in_traverse(root); // print list of items
    fflush(stdout);
    char operation[MAXLEN];
    for (int i = 0; i < num_operations; i++) {
        scanf("%s", operation);

        if (strcmp(operation, "find") == 0) {
            scanf("%s %s", category, item);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                itemNode *foundItem = searchItemNode(tree->theTree, item);
                if (foundItem != NULL) {
                    printf("%d %s found in %s\n", foundItem->count, item, category);
                } else {
                    printf("%s not found in %s\n", item, category);
                }
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "count_before") == 0) {
            scanf("%s %s", category, item);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                int result = count_before(tree->theTree, item);
                printf("item before %s: %d\n", item, result);
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "check_balance") == 0) {
            scanf("%s", category);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                int height, left_height, right_height;
                bool balanced = is_balanced(tree->theTree, &height, &left_height, &right_height);
                printf("%s: left height %d, right height %d, difference %d, %s\n", category, left_height, right_height, abs(left_height - right_height), balanced ? "balanced" : "not balanced");
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "count") == 0) {
            scanf("%s", category);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                int result = count_items(tree->theTree);
                printf("%s count %d\n", category, result);
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "remove") == 0) {
            scanf("%s %s", category, item);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                tree->theTree = remove_item(tree->theTree, item);
                printf("%s deleted from %s\n", item, category);
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "insert") == 0) {
            scanf("%s %s %d", category, item, &value);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                tree->theTree = insertItemNode(tree->theTree, item, value);
                printf("%s inserted into %s\n", item, category);
            } else {
                printf("%s does not exist\n", category);
            }
        } else if (strcmp(operation, "delete_name") == 0) {
            scanf("%s", category);
            root = delete_name(root, category);
            printf("%s deleted\n", category);
        } else if (strcmp(operation, "decrease") == 0) {
            scanf("%s %s %d", category, item, &value);
            treeNameNode *tree = searchNameNode(root, category);
            if (tree != NULL) {
                tree->theTree = decrease(tree->theTree, item, value);
                printf("%s reduced\n", item);
            } else {
                printf("%s does not exist\n", category);
            }
        } else {
            printf("Invalid operation: %s\n", operation);
        }
    }

    // Free memory
    freeTree(root);
    //fclose(file);
    return 0;
}
