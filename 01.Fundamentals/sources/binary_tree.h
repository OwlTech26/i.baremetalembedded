/** @file binary_tree.h
*
* @brief Header file of binary tree implementation.
*
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// === Type Definitions ===
//
typedef struct treeNode
{
    int key;
    struct treeNode *left;
    struct treeNode *right;
} treeNode_t;

typedef struct captureType
{
    int *key;
    int captureSize;
    size_t captureLimit;
    bool b_overFlow;
} captureType_t;

// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
void *CreateBinSearchTree (treeNode_t **pp_root, int *p_data, size_t dataSize);
void InitCapture (captureType_t *p_capture, const size_t captureLimit);
void ResetCapture (captureType_t *p_capture);
void CleanupCapture (captureType_t *p_capture);
void InorderTraversal (treeNode_t *p_root, captureType_t *p_capture);
void PreorderTraversal (treeNode_t *p_root, captureType_t *p_capture);
void PostorderTraversal (treeNode_t *p_root, captureType_t *p_capture);
treeNode_t *BinaryTreeSearch (treeNode_t *p_root, const int data);
void DestroyTree (treeNode_t *p_root);


#endif // BINARY_TREE_H

/*** EOF ***/

/** @file binary_tree.h
*
* @brief Header file of binary tree implementation.
*
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

// === Type Definitions ===
//
typedef struct treeNode
{
    int key;
    struct treeNode *left;
    struct treeNode *right;
} treeNode_t;

typedef struct stackType
{
    ↨int key;
    size_t top;
} stackType_t;

// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
void *CreateBinSearchTree (treeNode_t **pp_root, int *p_data, size_t dataSize);
void InorderTraversal (treeNode_t *p_root);


#endif // BINARY_TREE_H

/*** EOF ***/

