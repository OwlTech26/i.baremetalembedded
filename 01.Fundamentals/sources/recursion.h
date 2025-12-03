/** @file recursion.h
*
* @brief Collection of basic recursive function header.
*
*/

#ifndef RECURSION_H
#define RECURSION_H

#include <stdio.h>
#include <math.h>
#include <string.h>

// === Type Definitions ===
//


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
void PrintHello (int n);
void JugglerSequence (int a);
unsigned int Factorial (unsigned int n);
int RecursiveBinarySearch (const int *p_data, int bottom, int top, const int target);
void RecursiveDecimalToBinary (unsigned int n, char *p_result);

#endif // RECURSION_H

/*** EOF ***/
