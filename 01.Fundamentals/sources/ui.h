/** @file ui.h
*
* @brief A description of the module's purpose.
*
*/

#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "test.h"

// === Constant Definitions ===
//
#define CALLBACK_LIMIT 10

// === Type Definitions ===
//
typedef int (*api_t) (int);
typedef struct callback
{
    int index;
    api_t call[CALLBACK_LIMIT];
} callback_t;


// === Macros ===
//


// === Public API Functions ===
//
void MenuInit (void);
void MenuPrint (const int exit);
void MenuUI (int *p_select, const int exit);

#endif /* UI_H */

/*** EOF ***/
