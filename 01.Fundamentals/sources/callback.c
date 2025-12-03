/** @file callback.c
*
*   @brief Simple Callback Functions
*
*/

#include "callback.h"

//=== Public Function API ===
//
int add (int a, int b)
{
    return (a + b);
}

int subtract (int a, int b)
{
    return (a - b);
}

int multiply (int a, int b)
{
    return (a * b);
}

int Callback (function_t *p_operation, int a, int b)
{
    return p_operation(a, b);
}


/*** EOF ***/

