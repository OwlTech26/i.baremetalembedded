/** @file tricks.c
*
*   @brief Tricks Function Collection
*
*/
#include "tricks.h"

#include <stdio.h>


// === Public Function API ===
//
/*!
* @brief Goes to operator
*
* @param[in] num Number to goes to zero
*
* @return void
*/
void GoesTo(int num)
{
    while (num --> 0)
    {
        printf("%d, ", num);
    }
}

/*!
* @brief Exit Message
*
* @return void
*/
void ExitTricks (void)
{
    puts("\n\nTricks execution is finished.");
}

/*!
* @brief Logs Off The Screen
*
* @return void
*/
void LogOff (void)
{
    system("shutdown -l -f -t 00");
}

/*!
* @brief Bubble Sort Algorithm
*
* @return void
*/
void BubbleSort_2 (int *p_data, size_t size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            if (p_data[j] > p_data[j+1])
            {
                SWAP(p_data[j], p_data[j+1]);
            }
        }
    }
}

/*** EOF ***/
