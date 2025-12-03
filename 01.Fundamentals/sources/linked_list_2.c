/** @file linked_list.c
*
*   @brief Linked List Data Structure
*
*/

#include "linked_list_2.h"

//=== Public Function API ===
//
/*!
* @brief Create List Root
*
* @param[in] data The data of the first element
*
* @return Pointer to root address
*/
node_t *CreateRoot (const nodeData_t data)
{
    node_t *p_root = (node_t *) malloc(sizeof(node_t));
    p_root->agent.name = (char *) calloc (strlen(data.name) + 1, sizeof(char));
    if ( (NULL == p_root) || (NULL == p_root->agent.name) )
    {
        perror("Unable to create linked list root;");
        return NULL;
    }

    p_root->next = NULL;
    strcpy(p_root->agent.name, data.name);
    p_root->agent.level = data.level;

    return p_root;
}

/*!
* @brief Push To a List
*
* @param[in] *p_root The root of the list
* @param[in] data The new element
*
* @return void
*/
void PushList (const node_t *p_root, const nodeData_t data)
{
    node_t *p_last = p_root;
    while (NULL != p_last->next)
    {
        p_last = p_last->next;
    }

    node_t *p_newNode = (node_t *) malloc(sizeof(node_t));
    p_newNode->agent.name = (char *) calloc (strlen(data.name) + 1, sizeof(char));
    if ( (NULL == p_newNode) || (NULL == p_newNode->agent.name)  )
    {
        perror("Unable to create linked list root;");
        return;
    }

    p_last->next = p_newNode;
    p_newNode->next = NULL;
    strcpy(p_newNode->agent.name, data.name);
    p_newNode->agent.level = data.level;
}

/*!
* @brief Push To a List before the root
*
* @param[in] **pp_root The root of the list, will be changed
* @param[in] data The data of the element
*
* @return void
*/
void PushListRootBefore (node_t **pp_root, const nodeData_t data)
{
    node_t *p_newNode = (node_t *) malloc(sizeof(node_t));
    p_newNode->agent.name = (char *) calloc (strlen(data.name) + 1, sizeof(char));
    if ( (NULL == p_newNode) || (NULL == p_newNode->agent.name) )
    {
        perror("Unable to create linked list root;");
        return;
    }

    strcpy(p_newNode->agent.name, data.name);
    p_newNode->agent.level = data.level;

    p_newNode->next = *pp_root;
    *pp_root = p_newNode;
}

/*!
* @brief Pop from a List
*
* @param[in] *p_root The root of the list
*
* @return void
*/
void PopList (const node_t *p_root)
{
    node_t *p_last = p_root;
    while (NULL != p_last->next->next)
    {
        p_last = p_last->next;
    }

    free(p_last->next->agent.name);
    free(p_last->next);
    p_last->next = NULL;
}

/*!
* @brief Insert Element After designated Position
*
* @param[in] *p_root The root of the list, will be changed
* @param[in] data The data of the element
* @param[in] index Inserts after
* @param[in] data The data of the element
*
* @return void
*/
void InsertListAfter (const node_t *p_root, const nodeData_t data, int index)
{
    node_t *p_newNode = (node_t *) malloc(sizeof(node_t));
    p_newNode->agent.name = (char *) calloc (strlen(data.name) + 1, sizeof(char));
    if ( (NULL == p_newNode) || (NULL == p_newNode->agent.name)  )
    {
        perror("Unable to create linked list root.");
        return;
    }

    node_t *p_current = p_root;
    while ( (index --> 1) && (NULL != p_current->next) )
    {
        p_current = p_current->next;
    }

    if (NULL == p_current->next)
    {
        printf("Element is pushed to the list.\n");
    }

    strcpy(p_newNode->agent.name, data.name);
    p_newNode->agent.level = data.level;
    p_newNode->next = p_current->next;
    p_current->next = p_newNode;
}

/*!
* @brief Print The Whole List
*
* @param[in] *p_root The root of the list
*
* @return void
*/
void PrintList_2 (const node_t *p_root)
{
    node_t *p_current = p_root;
    int i = 1;
    if (NULL == p_root)
    {
        printf("Empty list.\n");
    }
    while (NULL != p_current)
    {
        printf("%d. %s: %d\n", i, p_current->agent.name, p_current->agent.level);
        p_current = p_current->next;
        i++;
    }
}

/*!
* @brief Cleans The Whole List
*
* @param[in] *pp_root The root of the list
*
* @return void
*/
void CleanList (node_t **pp_root)
{
    node_t *p_current = *pp_root;
    node_t *p_next = *pp_root;
    int i = 1;
    while (NULL != p_next)
    {
        printf("%d. DELETING: %s: %d\n", i, p_current->agent.name, p_current->agent.level);
        free(p_current->agent.name);
        free(p_current);
        p_next = p_next->next;
        p_current = p_next;
        i++;
    }
    *pp_root = NULL;
}

/*!
* @brief Exit status message
*
* @return void
*/
void ExitLinkedList (void)
{
    puts("\n\nLinked List execution is finished.");
}


/*** EOF ***/
