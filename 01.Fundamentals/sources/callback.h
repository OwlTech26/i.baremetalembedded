/** @file callback.h
*
*   @brief Simple Callback's Header
*
*/

#ifndef CALLBACK_H
#define CALLBACK_H

//=== Type Definitions ===
//
typedef int function_t (int a, int b);

//=== Constant Definitions ===
//

//=== Public Function API ===
//
int add (int a, int b);
int subtract (int a, int b);
int multiply (int a, int b);

int Callback (function_t *p_operation, int a, int b);

#endif // CALLBACK_H

/*** EOF ***/
