/** @file tricks.h
*
*   @brief Tricks header file
*
*/

#ifndef TRICKS_H
#define TRICKS_H

#include <stdlib.h>
#include <windows.h>
#include <time.h>

// === Type Definitions ===
//
typedef struct testNumOf
{
    int a;
    int b;
    char *name;
} testNumOf_t;

typedef struct binaryData
{
    int a;
    int b;
} binaryData_t;

// === Macro Definitions ===
//
#define NUM_OF(x)       (sizeof(x) / sizeof(*x))           // Macro To Get Array Size Of Any Data Type
#define SWAP(a ,b)      { a ^= b; b^= a; a^= b; }          // Generic Swap values

// Execution Measurement
clock_t startTimer, stopTimer;
#define START_TIMER     if ( (startTimer = clock()) == -1) \
                        { \
                            perror("Unable to start time measurement.");\
                        }
#define STOP_TIMER      if ( (stopTimer = clock() == -1) ) \
                        {\
                            perror("Unable to stop time measurement.");\
                        }
#define GET_ELAPSED(x)  (x = ((double)stopTimer - startTimer) / CLOCKS_PER_SEC)

// === Public API Functions Prototypes ===
//
void GoesTo(int num);
void ExitTricks (void);
void LogOff (void);
void BubbleSort_2 (int *p_data, size_t size);

#endif // TRICKS_H

/*** EOF ***/
