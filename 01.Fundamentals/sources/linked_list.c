/** @file linked_list.c
*
* @brief Doubly linked list implementation with sorted insertion.
*
*/

#include "linked_list.h"

// === Protected Functions ===
//
/*!
* @brief Inserts data at head.
*
* @param[in] **pp_list Pointer to the list pointer
* @param[in] **pp_node Pointer to the node pointer to be inserted
*
* @return void
*/
static inline void InsertHead (list_t **pp_list, node_t **pp_node)
{
    (*pp_node)->next = (*pp_list)->head;
    (*pp_node)->prev = NULL;
    (*pp_list)->head->prev = *pp_node;
    (*pp_list)->head = *pp_node;
    (*pp_list)->listSize++;
}

/*!
* @brief Inserts data at tail.
*
* @param[in] **pp_list Pointer to the list pointer
* @param[in] **pp_node Pointer to the node pointer to be inserted
*
* @return void
*/
static inline void InsertTail (list_t **pp_list, node_t **pp_node)
{
    (*pp_node)->prev = (*pp_list)->tail;
    (*pp_node)->next = NULL;
    (*pp_list)->tail->next = *pp_node;
    (*pp_list)->tail = *pp_node;
    (*pp_list)->listSize++;
}

/*!
* @brief Insert before reference node.
*
* @param[in] **pp_list Pointer to the list pointer
* @param[in] **pp_node Pointer to the node pointer to be inserted
* @param[in] **pp_nodeRef Pointer to the reference node pointer
*
* @return void
*/
static inline void InsertBefore (list_t **pp_list, node_t **pp_node, node_t **pp_nodeRef)
{
    (*pp_node)->prev = (*pp_nodeRef)->prev;
    (*pp_node)->next = *pp_nodeRef;
    (*pp_nodeRef)->prev->next = *pp_node;
    (*pp_nodeRef)->prev = *pp_node;
    (*pp_list)->listSize++;
}

// === Public API Functions ===
//
/*!
* @brief Initializes the doubly linked list.
*
* @param[in] *p_list Pointer to the list
*
* @return TRUE: Success, FALSE: Fail
*/
bool InitializeList (list_t *p_list)
{
    if (NULL == p_list)
    {
        return false;
    }

    p_list->listSize = 0;
    p_list->head = NULL;
    p_list->tail = NULL;

    return true;
}

/*!
* @brief Seeks a designated node by index.
*
* @param[in] *p_list Pointer to the list
* @param[in] index The indey of the node in the list
*
* @return Node = List(index)
*/
node_t *SeekNode (list_t *p_list, const int index)
{
    if ( (NULL == p_list) || index > p_list->listSize )
    {
        return NULL;
    }

    if (0 == index)
    {
        return p_list->head;
    }

    if (index == p_list->listSize)
    {
        return p_list->tail;
    }

    bool dir = ( index > ((p_list->listSize) >> 1) );               // TRUE: start the search from the tail, otherwise from the head
    node_t *p_currentNode = (dir) ? p_list->tail : p_list->head;

    int i = (dir) ? p_list->listSize : 1;

    while (index != i)
    {
        if (dir) // From the tail
        {
            p_currentNode = p_currentNode->prev;
            i--;
        }
        else    // From the head
        {
            p_currentNode = p_currentNode->next;
            ++i;
        }
    }

    return p_currentNode;
}

/*!
* @brief Sorted insertion into the list.
*
* @param[in] *p_list Pointer to the list
* @param[in] data The data to be inserted.
*
* @return TRUE: Success, FALSE: Fail
*/
bool InsertListItem (list_t *p_list, int data)
{
    node_t *p_newNode = (node_t *) malloc(sizeof(node_t));
    if ( (NULL == p_newNode) || (NULL == p_list) )
    {
        return false;
    }
    p_newNode->value = data;

    if (0 == p_list->listSize)
    {
        p_newNode->prev = NULL;
        p_newNode->next = NULL;
        p_list->head = p_newNode;
        p_list->tail = p_newNode;
        p_list->listSize++;
        return true;
    }

    if (data < p_list->head->value)
    {
        InsertHead(&p_list, &p_newNode);
        return true;
    }

    if (data > p_list->tail->value)
    {
        InsertTail(&p_list, &p_newNode);
        return true;
    }

    node_t *p_refNode = p_list->head;
    while ( (data > p_refNode->value) && (NULL != p_refNode) )
    {
        p_refNode = p_refNode->next;
    }

    InsertBefore(&p_list, &p_newNode, &p_refNode);

    return true;
}

/*!
* @brief Deleting a list node by index.
*
* @param[in] *p_list Pointer to the list
* @param[in] index The index of the node.
*
* @return Returns with the deleted data
*/
int DeleteListItem (list_t *p_list, const int index)
{
    if ( (NULL == p_list) || (index > p_list->listSize) || (index < 1))
    {
        return -99999;
    }

    node_t *p_currentNode;
    int data;

    if (1 == index)                             // Index at the head
    {
        p_currentNode = p_list->head;
        p_list->head = p_currentNode->next;
        p_currentNode->next->prev = NULL;
    }
    else if (index == p_list->listSize)         // Index at the tail
    {
        p_currentNode = p_list->tail;
        p_list->tail = p_currentNode->prev;
        p_currentNode->prev->next = NULL;
    }
    else                                        // Default Index
    {
        p_currentNode = SeekNode(p_list, index);
        p_currentNode->prev->next = p_currentNode->next;
        p_currentNode->next->prev = p_currentNode->prev;
    }

    data = p_currentNode->value;
    p_list->listSize--;
    free(p_currentNode);

    return data;
}

/*!
* @brief Prints out the list.
*
* @param[in] *p_list Pointer to the list
* @param[out] *p_data Output data to be printed
* @param[in] reverseDir FALSE: left to right, TRUE: right to left
*
* @return void
*/
void PrintList (list_t *p_list, int *p_data, bool reverseDir)
{
    if (NULL == p_list)
    {
        return;
    }

    node_t *p_current = (reverseDir) ? p_list->tail : p_list->head;

    while (NULL != p_current)
    {
        *p_data = p_current->value;
        p_current = (reverseDir) ? p_current->prev : p_current->next;
        p_data++;
    }
}

/*!
* @brief Deallocates the list.
*
* @param[in] *p_list Pointer to the list
*
* @return void
*/
void CleanUpList (list_t *p_list)
{
    if (NULL == p_list)
    {
        return;
    }

    node_t *p_current = p_list->head;
    node_t *p_next = p_list->head;
    while (NULL != p_next->next)
    {
        p_current = p_next;
        p_next = p_current->next;
        free(p_current);
    }
}

/*** EOF ***/

