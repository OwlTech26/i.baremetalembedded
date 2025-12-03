/** @file test.h
*
* @brief Header of Simple Test Procedures
*
*/

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <time.h>

#include "common.h"
#include "queue.h"
#include "linked_list.h"
#include "binary_search.h"
#include "recursion.h"
#include "binary_tree.h"
#include "morse.h"
#include "sorting.h"


// === Type Definitions ===
//


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
int TestQueue (int x);
int TestBinarySearch (int x);
int TestRecursion (int x);
int TestBinarySearchTree (int x);
int TestMorse (int x);
int TestHeap (int x);
int TestSorting(int x);

#endif /* TEST_H */

/*** EOF ***/

