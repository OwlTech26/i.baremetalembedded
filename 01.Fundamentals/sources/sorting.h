/** @file sorting.h
*
* @brief Header for sorting algorithm function collection.
*
*/

#ifndef SORTING_H
#define ORTING_H

#include <stdio.h>
#include <stdbool.h>

#include "common.h"

// === Type Definitions ===
//


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
void SelectionSort (int *p_data, size_t dataSize);
void BubbleSort (int *p_data, size_t dataSize);
void InsertionSort (int *p_data, size_t dataSize);
void ShellSort (int *p_data, size_t dataSize, int incrMax);
void MergingSortedArrays (int *p_data1, int *p_data2, int *p_result, size_t dataSize1, size_t dataSize2, int *p_resultSize);
void MergeSort (int data[], int low, int up);
void HeapSort (int *p_data, size_t dataSize);
void QuickSort (int data[], int low, int up);

#endif // SORTING_H

/*** EOF ***/
