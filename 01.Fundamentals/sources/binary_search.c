/** @file binary_search.c
*
* @brief Binary search algorithm implementation.
*        It uses doubly linked list with sorted insertion.
*
*/

#include "binary_search.h"

// === Protected Functions ===
//


// === Public API Functions ===
//
/*!
* @brief Binary searching.
*
* @param[in] *p_list Pointer to the list
* @param[in] data Data to be searched
*
* @return The search index: -1 if not found, otherwise the wanted data at the index.
*/
int BinarySearch (list_t *p_list, const int data)
{
    int bottom = 1;
    int top = p_list->listSize;
    int middle = (top + bottom) >> 1;
    int index = -1;

    if (NULL == p_list)
    {
        return index;
    }

    node_t *p_currentNode;

    while (top >= bottom)
    {
        p_currentNode = SeekNode(p_list, middle);
        if (data == p_currentNode->value)
        {
            index = middle;
            break;
        }
        if (data < p_currentNode->value)
        {
            top = middle - 1;
            middle = (top + bottom) >> 1;
        }
        else
        {
            bottom = middle + 1;
            middle = (top + bottom) >> 1;
        }
    }

    return index;
}

/*** EOF ***/
