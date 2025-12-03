/** @file binary_tree.c
*
* @brief Binary tree implementation.
*
*/

#include "binary_tree.h"


// === Protected Functions ===
//
/*!
* @brief Sorted insertion for binary tree search.
*        Left side: smaller data; Right side: greater or equal data
*
* @param[in] *p_root The root of the tree
* @param[in] key Data to be inserted
*
* @return void
*/
static void InsertTreeNode (treeNode_t **pp_root, int key)
{
    if (NULL == *pp_root)
    {
        *pp_root = (treeNode_t *)malloc(sizeof(treeNode_t));
        if (NULL == *pp_root)
        {
            perror("Insufficient memory fatal error.\n");
            exit(-1);
        }

        (*pp_root)->key = key;
        (*pp_root)->left = NULL;
        (*pp_root)->right = NULL;
    }
    else if (key > (*pp_root)->key)
    {
        InsertTreeNode( &((*pp_root)->right), key);
    }
    else if (key < (*pp_root)->key)
    {
        InsertTreeNode( &((*pp_root)->left), key);
    }
    else
    {
        printf("Duplicated data found (%d), insertion is aborted.\n", key);
    }
}

/*!
* @brief Creates Binary Tree for Binary Search.
*
* @param[in] *p_root Root of the binary tree
* @param[in] **pp_data Input array data.
* @param[in] dataSize The size of the input data array.
*
* @return void
*/
static inline void CaptureKey (captureType_t *p_capture, const int key)
{
    if (p_capture->captureSize == (p_capture->captureLimit - 1))
    {
        p_capture->b_overFlow = true;
        return;
    }

    p_capture->captureSize++;
    p_capture->key[p_capture->captureSize] = key;
}

/*!
* @brief Creates Binary Tree for Binary Search.
*
* @param[in] *p_root Root of the binary tree
* @param[in] **pp_data Input array data.
* @param[in] dataSize The size of the input data array.
*
* @return void
*/

// === Public API Functions ===
//
/*!
* @brief Creates Binary Tree for Binary Search.
*
* @param[in] *p_root Root of the binary tree
* @param[in] **pp_data Input array data.
* @param[in] dataSize The size of the input data array.
*
* @return void
*/
void *CreateBinSearchTree (treeNode_t **pp_root, int *p_data, size_t dataSize)
{
    if (0 == dataSize)
    {
        perror("Empty data to be inserted.\n");
        return;
    }

    for (int i = 0; i < dataSize; ++i)
    {
        InsertTreeNode(pp_root, p_data[i]);
    }
}

/*!
* @brief Initializes data structure for data capture at traversal.
*
* @param[in] *p_capture Data capture structure
* @param[in] captureLimit Limitation of data size
*
* @return void
*/
void InitCapture (captureType_t *p_capture, const size_t captureLimit)
{
    p_capture->captureSize = -1;
    p_capture->captureLimit = captureLimit;
    p_capture->b_overFlow = false;

    p_capture->key = (int *)calloc(captureLimit, sizeof(int));
    if (NULL == p_capture)
    {
        perror("Insufficient memory.\n");
    }
}

/*!
* @brief Resets the captured keys.
*
* @param[in] *p_capture Data capture structure
*
* @return void
*/
void ResetCapture (captureType_t *p_capture)
{
    p_capture->captureSize = -1;
    p_capture->b_overFlow = false;
}

/*!
* @brief Cleanups the captured keys.
*
* @param[in] *p_capture Data capture structure
*
* @return void
*/
void CleanupCapture (captureType_t *p_capture)
{
    free(p_capture->key);
}

/*!
* @brief Inorder Traversal (left-root-right).
*
* @param[in] *p_root Root of the binary tree
* @param[out] *p_capture The captured data to be saved
*
* @return void
*/
void InorderTraversal (treeNode_t *p_root, captureType_t *p_capture)
{
    if (NULL != p_root)
    {
        InorderTraversal(p_root->left, p_capture);
        CaptureKey(p_capture, p_root->key);
        InorderTraversal(p_root->right, p_capture);
    }
    else
    {
        return;
    }
}

/*!
* @brief Preorder Traversal (root-left-right).
*
* @param[in] *p_root Root of the binary tree
* @param[out] *p_capture The captured data to be saved
*
* @return void
*/
void PreorderTraversal (treeNode_t *p_root, captureType_t *p_capture)
{
    if (NULL != p_root)
    {
        CaptureKey(p_capture, p_root->key);
        PreorderTraversal(p_root->left, p_capture);
        PreorderTraversal(p_root->right, p_capture);
    }
    else
    {
        return;
    }
}

/*!
* @brief Postorder Traversal (left-right-root).
*
* @param[in] *p_root Root of the binary tree
* @param[out] *p_capture The captured data to be saved
*
* @return void
*/
void PostorderTraversal (treeNode_t *p_root, captureType_t *p_capture)
{
    if (NULL != p_root)
    {
        PostorderTraversal(p_root->left, p_capture);
        PostorderTraversal(p_root->right, p_capture);
        CaptureKey(p_capture, p_root->key);
    }
    else
    {
        return;
    }
}

/*!
* @brief Binary search for binary tree.
*
* @param[in] *p_root Root of the binary tree
* @param[in] data Data to be found
*
* @return With the found node. NULL in case of no match.
*/
treeNode_t *BinaryTreeSearch (treeNode_t *p_root, const int data)
{
    if (NULL == p_root)
    {
        return NULL;
    }
    else if (data == p_root->key)
    {
        return p_root;
    }
    else if (data < p_root->key)
    {
        BinaryTreeSearch(p_root->left, data);
    }
    else
    {
        BinaryTreeSearch(p_root->right, data);
    }
}

/*!
* @brief Cleanups the tree via Postorder Traversal (left-right-root).
*
* @param[in] *p_root Root of the binary tree
*
* @return void
*/
void DestroyTree (treeNode_t *p_root)
{
    if (NULL != p_root)
    {
        DestroyTree(p_root->left);
        DestroyTree(p_root->right);
        free(p_root);
    }
    else
    {
        return;
    }
}

/*** EOF ***/

