/** @file stack.c
*
*   @brief Basic stack implementation.
*
*/

#include <stdio.h>

#include "stack.h"

// === Private Functions ===
//

// === Public Function API ===
//
/*!
*  @brief Allocates Memory for the Stack Element
*
*  @param[in] size The required size of the stack
*
*  @return 0: Success, 1: Fail
*/
int InitializeStack(t_stack *p_stack, size_t size)
{
    p_stack->item = (int *) calloc(size, sizeof(int));
    if (NULL == p_stack->item)
    {
        perror("Unable to allocate stack.\n");
        return -1;
    }

    p_stack->size = size;
    p_stack->top = -1;

    return 0;
}

/*!
*  @brief Inserts Data to the Top of the Stack
*
*  @param[in] *p_stack Pointer to the stack
*  @param[in] data The value to be inserted
*
*  @return void
*/
void PushStack (t_stack *p_stack, int data)
{
    if (p_stack->top == (p_stack->size - 1))
    {
        // Reallocate memory for doubled stack
        int *p_tempItem = (int *) calloc(2 * p_stack->size, sizeof(int));
        if (NULL == p_tempItem)
        {
            perror("Stack is overflow.\n");
            return;
        }
        for (int i = 0; i < p_stack->size; i++)
        {
            p_tempItem[i] = p_stack->item[i];
        }
        CleanupStack(p_stack);
        p_stack->item = p_tempItem;
        p_stack->size *= 2;
    }

    p_stack->top++;
    p_stack->item[p_stack->top] = data;
}

/*!
*  @brief Removes a Single Data from the Top of the Stack
*
*  @param[in] *p_stack Pointer to the stack pointer
*
*  @return The current value on the top of the stack
*/
int PopStack (t_stack *p_stack)
{
    if (-1 == p_stack->top)
    {
        perror("Stack is underflow.\n");
        return -9999;
    }

    int data = p_stack->item[p_stack->top];
    p_stack->top--;

    return data;
}

/*!
*  @brief Reads the Top Item from the Stack
*
*  @param[in] *p_stack Pointer to the stack
*
*  @return The item on the top
*/
int GetStackItem (t_stack *p_stack)
{
    return p_stack->item[p_stack->top];
}

/*!
*  @brief Gets the Size of the Stack
*
*  @param[in] *p_stack Pointer to the stack
*
*  @return The actual size
*/
size_t GetStackSize (t_stack *p_stack)
{
    return p_stack->size;
}

/*!
*  @brief Gets the Current Top Status of the Stack
*
*  @param[in] *p_stack Pointer to the stack
*
*  @return -1: Underflow, > -1: Normal
*/
int GetStackTop (t_stack *p_stack)
{
    return p_stack->top;
}

/*!
*  @brief Obtains the empty status of the stack
*
*  @param[in] *p_stack Pointer to the stack
*
*  @return -1: Empty, > -1: Not empty
*/
int StackIsEmpty (t_stack *p_stack)
{
    return (-1 == p_stack->top) ? 1 : 0;
}

/*!
*  @brief Cleans the Allocated Memory for Stack Items
*
*  @param[in] *p_stack Pointer to the stack
*
*  @return void
*/
void CleanupStack (t_stack *p_stack)
{
    if (NULL != p_stack->item)
    {
        free(p_stack->item);
    }
}

/**** EOF ***/
