/** @file stack.h
*
*   @brief Basic stack implementation header file.
*
*/

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

// === Constant Definitions ===
//

// === Type Definitions ===
//
typedef struct stackType
{
    int *item;
    size_t size;
    int top;
} t_stack;


// === Macros ===
//


// === Public Function API ===
//
int InitializeStack(t_stack *p_stack, size_t size);
void PushStack (t_stack *p_stack, int data);
int PopStack (t_stack *p_stack);
int GetStackItem (t_stack *p_stack);
size_t GetStackSize (t_stack *p_stack);
int GetStackTop (t_stack *p_stack);
int StackIsEmpty (t_stack *p_stack);
void CleanupStack (t_stack *p_stack);


#endif // STACK_H

/**** EOF ***/
