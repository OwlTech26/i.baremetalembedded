/** @file linked_list.h
*
* @brief The header file of doubly linked list data structure.
*
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

// === Type Definitions ===
//
typedef struct node
{
  int value;
  struct node *next;
  struct node *prev;
} node_t;

typedef struct listType
{
    size_t listSize;
    struct node *head;
    struct node *tail;
} list_t;


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
bool InitializeList (list_t *p_list);
node_t *SeekNode (list_t *p_list, const int index);
bool InsertListItem (list_t *p_list, int data);
int DeleteListItem (list_t *p_list, const int index);
void PrintList (list_t *p_list, int *p_data, bool reverseDir);
void CleanUpList (list_t *p_list);

#endif // LINKED_LIST_H

/*** EOF ***/
