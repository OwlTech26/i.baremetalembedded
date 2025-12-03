/** @file queue.h
*
*   @brief Circular queue header file
*
*/

#ifndef QUEUE_2_H
#define QUEUE_2_H

#include <stdio.h>
#include <stdlib.h>

//=== Constant Defintions ===
//
#define QUEUE_SIZE      16


//=== Public Function API Prototypes
//
int *InitializeQueue (int *p_front, int *p_rear, size_t qSize);

#endif // QUEUE_2_H

/*** EOF ***/
