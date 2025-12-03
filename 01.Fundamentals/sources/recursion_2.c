/** @file recursion.h
*
*   @brief Recursion Function Collection
*
*/

#include "recursion_2.h"

//=== Public APIs ===
//
/*!
* @brief Factorial(n)
*
* @param[in] n The number of factorial
*
* @return Fact(n)
*/
int Factorial_2 (int n)
{
    if (n)
    {
        return (n * Factorial(n-1));
    }
    else
    {
        return 1;
    }
}

/*!
* @brief Fibonacci(n)
*
* @param[in] n The number of Fibonacci sum
*
* @return Fib(n)
*/
int Fibonacci (int n)
{
    if (n)
    {
        return (n + Fibonacci(n-1));
    }
    else
    {
        return 0;
    }
}

/*!
* @brief Power of 10^n unsigned integer
*
* @param[in] n The exponential number
*
* @return 10^n unsigned integer
*/
unsigned int Pow10Int (unsigned int n)
{
    if (n)
    {
        return (10 * Pow10Int(n-1));
    }
    {
        return 1;
    }
}

/*!
* @brief Bitwise addition
*
* @param[in] x Member of addition
*
* @param[in] y Member of addition
*
* @return The summary
*/
int BitwiseAdd (int x, int y)
{
    if (0 == y)
    {
        return x;
    }
    else
    {
        return BitwiseAdd( x ^ y, (x & y) << 1 );
    }
}



/*** EOF ***/
