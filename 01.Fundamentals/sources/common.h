/** @file common.h
*
*   @brief Basic stack implementation header file.
*
*/

#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

// === Constant Definitions ===
//

// === Type Definitions ===
//
typedef void menu_t (int a);

// === Macros ===
//
#define SWAP(a, b)  {a ^= b; b ^= a; a ^= b;}
#define NUM_OF(x)   (sizeof(x) / sizeof(*x))

// === Public Function API ===
//


#endif // COMMON_H

/**** EOF ***/
