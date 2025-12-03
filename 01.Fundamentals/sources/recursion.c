/** @file recursion.c
*
* @brief Collection of basic recursive function.
*
*/

#include "recursion.h"

// === Protected Functions ===
//


// === Public API Functions ===
//
/*!
* @brief Prints HELLO to the console recursively
*
* @param[in] n Number of times of printing
*
* @return void
*/
void PrintHello (int n)
{
    if (n <= 0)
    {
        return;
    }

    PrintHello(--n);
    puts("HELLO!");
}

/*!
* @brief Juggler Sequence
*
* @param[in] a Parameter in the calculation
*
* @return 0
*/
void JugglerSequence (int a)
{
    if (1 == a)
    {
        printf("%d, ", a);
        return;
    }

    JugglerSequence( (a & 0x1) ? (int)pow(a, 1.5) : (int)pow(a, 0.5));
    printf("%d, ", a);
}

/*!
* @brief Factorial calculation
*
* @param[in] n Parameter for calculation
*
* @return n!
*/
unsigned int Factorial (unsigned int n)
{
    if (0 == n)
    {
        return 1;
    }

    return n * Factorial(n - 1);
}

/*!
* @brief Recursive Binary Search
*
* @param[in] *p_data The input array
* @param[in] bottom The bottom of the search
* @param[in] bottom The top of the search
* @param[in] target The target to be searched
*
* @return -1: Not found, Otherwise the index
*/
int RecursiveBinarySearch (const int *p_data, int bottom, int top, const int target)
{
    if (top < bottom)
    {
        return -1;
    }

    int middle = (top + bottom) >> 1;
    if (target == p_data[middle])
    {
        return middle;
    }

    if (p_data[middle] > target)
    {
        return RecursiveBinarySearch(p_data, bottom, --middle, target);
    }
    else
    {
        return RecursiveBinarySearch(p_data, ++middle, top, target);
    }
}

/*!
* @brief Decimal to binary conversion
*
* @param[in] n The number to be converted
* @param[out] *p_result The converted string
*
* @return void
*/
void RecursiveDecimalToBinary (unsigned int n, char *p_result)
{
    if ( (0 == n) || (1 == n) )
    {
        strncat(p_result, (n) ? "1" : "0", 1);
        return;
    }

    RecursiveDecimalToBinary(n >> 1, p_result);
    strncat(p_result, (n & 0x1) ? "1" : "0", 1);
}
/*** EOF ***/




