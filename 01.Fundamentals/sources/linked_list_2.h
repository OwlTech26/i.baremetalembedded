/** @file linked_list.h
*
*   @brief Linked List Data Structure
*
*/

#ifndef LINKED_LIST_2_H
#define LINKED_LIST_2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=== Constant Defintions ===
//

//=== Type Defintions ===
//
typedef struct nodeData
{
    char *name;
    int level;
} nodeData_t;

typedef struct node
{
    nodeData_t agent;
    struct node *next;
} node_t;

//=== Macros ===
//

//=== Constant Defintions ===
//


//=== Public Functions API Prototypes ===
//
node_t *CreateRoot (const nodeData_t data);
void PushList (const node_t *p_root, const nodeData_t data);
void PushListRootBefore (node_t **pp_root, const nodeData_t data);
void PopList (const node_t *p_root);
void InsertListAfter (const node_t *p_root, const nodeData_t data, int index);
void CleanList (node_t **pp_root);
void PrintList_2 (const node_t *p_root);

void ExitLinkedList (void);

#endif // LINKED_LIST_H

/*** EOF ***/
