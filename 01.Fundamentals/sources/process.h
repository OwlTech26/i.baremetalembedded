/** @file process.h
*
* @brief Header of collection of the execution process
*
*/

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"
#include "ui.h"

// === Type Definitions ===
//


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
int PrintToBinary (int n);
int ReverseText (int x);
int BracketCheck (int x);
int InfixToPostfix (int x);


#endif /* PROCESS_H */

/*** EOF ***/

