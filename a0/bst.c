#include "bst.h"
#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc, free
#include <stdbool.h>
#include <stdio.h>

// This function automatically creates a node dynamically and assigns defaults
struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node)); // Dynamically allocate a node
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert_into(struct Node **root, int value)
{
    struct Node *newNode = createNode(value); // Create that new node dynamically
    struct Node *current;
    struct Node *trailCurrent = NULL;

    // Case Fault for empty tree
    if (*root == NULL)
    {
        //printf("Tree empty, first node: %d\n", newNode->value);
        *root = newNode;
    }
    else // For a non-empty tree
    {
        current = *root;
        while (current != NULL) // Iterate for every node that isnt null
        {
            trailCurrent = current;
            if (current->value == value) // Dupe case
            {
                free(newNode); // Free the memory!
                return;
            }
            else if (current->value > value) // Smaller case
            {
                //printf("Going left..");
                current = current->left; // Go left
            }
            else // Bigger case
            {
                //printf("Going right..");
                current = current->right; // Go right
            }
        }
        if (trailCurrent->value > value)
        {
            //printf("Insert LEFT: %d\n", newNode->value);
            trailCurrent->left = newNode;
        }
        else
        {
            //printf("Insert RIGHT: %d\n", newNode->value);
            trailCurrent->right = newNode;
        }
    }
}

void free_tree(struct Node *root)
{
    if (root == NULL) // Empty Tree case
    {
        return;
    }
    free_tree(root->left);  // Entire left side
    free_tree(root->right); // Entire right side
    free(root);             // Free the head
}

size_t size_of(const struct Node *root)
{
    int count = 0;
    if (root != NULL)
    {
        count = count + size_of(root->left);  // Size of left side
        count = count + size_of(root->right); // Size of right side
        count++;                              // Size of head
    }
    return count;
}

void treeToArray(const struct Node *root, int *arr, int *index)
{
    if (root != NULL)
    {

        treeToArray(root->left, arr, index);  // Left side
        arr[*index] = root->value;            // Actually add the current node to the array in order
        (*index)++;                           // Add current node immediate
        treeToArray(root->right, arr, index); // Add the right side in order
    }
}

int *contents_of(const struct Node *root)
{
    int *dynamicArray = NULL; // Create an empty dynamic array
    int arraySize = 0;
    int i = 0;        // Index
    int *iPtr = &i;   // Index Ptr
    if (root == NULL) // Empty tree case
    {
        return NULL;
    }
    arraySize = size_of(root);                      // Size of the tree
    dynamicArray = malloc(sizeof(int) * arraySize); // Allocate enough memory
    treeToArray(root, dynamicArray, iPtr);          // Convert it to an array
    return dynamicArray;                            // return the entire array
}

void treeToList(const struct Node *root, struct Node *arr, int *index)
{
    if (root != NULL)
    {

        treeToList(root->left, arr, index); // Left side iteration
        arr[*index] = *root;                // Current node assignment
        //printf("Setting [%d] = %d\n", *index, root->value);
        (*index)++;                          // Increment count
        treeToList(root->right, arr, index); // Right side iteration
    }
}

const struct Node *second_min_in(const struct Node *root)
{

    struct Node *dynamicArray = NULL; // Create an empty dynamic array
    int arraySize = 0;
    int i = 0;        // Index
    int *iPtr = &i;   // Index Ptr
    if (root == NULL) // Empty Tree Case
    {
        return NULL;
    }
    arraySize = size_of(root);                              // Size of tree
    dynamicArray = malloc(sizeof(struct Node) * arraySize); // Dynamically allocated for Size of Node * Size of Tree
    treeToList(root, dynamicArray, iPtr);                   // Convert the tree into a array of nodes

    struct Node *returnNode = malloc(sizeof(struct Node));
    *returnNode = dynamicArray[1];
    free(dynamicArray);
    return returnNode; // return 2nd element.
    /* // Broken algorithm
    const struct Node *current = root;
    const struct Node *prev = current;

    bool found = false;

    while (found != true)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
        {

            if (current->left == NULL)
            {
                if (root == current)
                {
                    current = current->right;
                }
                else
                {
                    //printf("FOUND 2nd MIN: %d", current->value);
                    return prev;
                }
            }
            else
            {
                //printf("Current: %d", current->value);
                //printf("LEFT: %d", current->left->value);
                prev = current;
                current = current->left;
            }
        }
    }
    return NULL;
    */
}
