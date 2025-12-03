/** @file sorting.c
*
* @brief Sorting function collection.
*
*/

#include "sorting.h"


// === Protected Functions ===
//
/*!
* @brief Merging two sorted parts of an array to a target array
*
* @param[in] *p_source The array source
* @param[out] *p_target The array to place the merged data
* @param[in] low1 Lower bound of Sorted Part 1
* @param[in] up1 Upper bound of Sorted Part 1
* @param[in] low2 Lower bound of Sorted Part 2
* @param[in] up2 Upper bound of Sorted Part 2
*
* @return void
*/
static void Merge (int *p_source, int *p_target, int low1, int up1, int low2, int up2)
{
    int i = low1;
    int j = low2;
    int k = low1;

    while ( (i <= up1) && (j <= up2) )
    {
        p_target[k++] = (p_source[i] <= p_source[j]) ? p_source[i++] : p_source[j++];
    }

    // Copy the remaining element
    while (i <= up1)
    {
        p_target[k++] = p_source[i++];
    }

    while (j <= up2)
    {
        p_target[k++] = p_source[j++];
    }
}

/*!
* @brief Copying source array data to the target array
*
* @param[out] *p_target The copied data
* @param[in] *p_source The data to be copied
* @param[in] low Lower bound
* @param[in] up Upper bound
*
* @return void
*/
static void Copy (int *p_target, int *p_source, int low, int up)
{
    for (int i = low; i <=up; ++i)
    {
        p_target[i] = p_source[i];
    }
}

/*!
* @brief Adjusting an array to a heap from the designated index
*
* @param[out] *p_data The data array to be adjusted
* @param[in] index The started index
* @param[in] p_heapSize The size of the heap
*
* @return void
*/
static void HeapAdjust (int *p_data, size_t index, size_t heapSize)
{
    int j = index << 1;          // Calculate left sibling
    int temp = p_data[index];

    while (j <= heapSize)
    {
        if ( (j < heapSize) && (p_data[j] < p_data[j+1]) )
        {
            j++;                // Calculate right sibling
        }
        if (temp > p_data[j])
        {
            break;
        }

        p_data[j >> 1] = p_data[j];
        j <<= 1;
    }

    p_data[j >> 1] = temp;
}

/*!
* @brief Reorganize array into a maximum heap
*
* @param[out] *p_data The array to be organized
* @param[in] heapSize The size of the input array
*
* @return void
*/
static void Heapify (int *p_data, size_t heapSize)
{
    for (int i = (heapSize >> 1); i >= 1; --i)
    {
        HeapAdjust(p_data, i, heapSize);
    }
}

/*!
* @brief Deleting from a maximum heap
*
* @param[out] *p_data The data array to be adjusted
* @param[out] *p_n The maximum index
*
* @return The deleted node
*/
static int HeapDelete (int *p_data, size_t *p_heapSize)
{
    if (0 == *p_heapSize)
    {
        perror("The heap is empty.\n");
        return -1;
    }

    int deleted = p_data[1];
    p_data[1] = p_data[*p_heapSize];

    (*p_heapSize)--;

    HeapAdjust(p_data, 1, *p_heapSize);

    return deleted;
}

/*!
* @brief Partioning for quick sorting algorithm
*
* @param[out] data[] The input data array
* @param[in] low Lower bound index
* @param[in] up Upper bound index
*
* @return Pivot index
*/
int Partition (int data[], int low, int up)
{
    int i = low + 1;
    int j = up;
    int pivot = data[low];

    while (i <= j)
    {
        while ( (data[i] < pivot) && (i < up) )
        {
            i++;
        }
        while (data[j] > pivot)
        {
            j--;
        }

        if (i < j)
        {
            SWAP(data[i], data[j]);
            i++;
            j--;
        }
        else            // Found the proper pilot's position
        {
            break;
        }
    }

    // j is the proper place for pivot
    data[low] = data[j];
    data[j] = pivot;

    return j;
}

// === Public API Functions ===
//
/*!
* @brief Selection sorting algorithm
*
* @param[out] *p_data The input data array
* @param[in] dataSize The full size of data
*
* @return void
*/
void SelectionSort (int *p_data, size_t dataSize)
{
    int minIndex;
    for (int i = 0; i < dataSize - 1; ++i)
    {
        minIndex = i;
        for (int j = i + 1; j < dataSize; ++j)
        {
            if (p_data[minIndex] > p_data[j])
            {
                minIndex = j;
            }
        }
        if (i != minIndex)
        {
            SWAP(p_data[i], p_data[minIndex]);
        }
    }
}

/*!
* @brief Bubble sorting algorithm
*
* @param[out] *p_data The input data array
* @param[in] dataSize The full size of data
*
* @return void
*/
void BubbleSort (int *p_data, size_t dataSize)
{
    bool b_swapped;
    for (int i = 0; i < dataSize - 1; ++i)
    {
        b_swapped = false;
        for (int j = 0; j < (dataSize - i - 1); ++j)
        {
            if (p_data[j] > p_data[j+1])
            {
                SWAP(p_data[j], p_data[j+1]);
                b_swapped = true;
            }
        }
        if (!b_swapped)
        {
            return;
        }
    }
}

/*!
* @brief Insertion sorting algorithm
*
* @param[out] *p_data The input data array
* @param[in] dataSize The full size of data
*
* @return void
*/
void InsertionSort (int *p_data, size_t dataSize)
{
    int temp, j;
    for (int i = 1; i < dataSize; ++i)
    {
        temp = p_data[i];
        for (j = i - 1; (j >= 0) && (p_data[j]) > temp; --j)
        {
            p_data[j+1] = p_data[j];
        }
        p_data[j+1] = temp;
    }
}

/*!
* @brief Shell sorting algorithm
*
* @param[out] *p_data The input data array
* @param[in] dataSize The full size of data
* @param[in] incrMax The maximum increment value
*
* @return void
*/
void ShellSort (int *p_data, size_t dataSize, int incrMax)
{
    int temp, j;
    while (incrMax >= 1)
    {
        for (int i = incrMax; i < dataSize; ++i)
        {
            temp = p_data[i];
            for (j = i - incrMax; (j >= 0) && (p_data[j] > temp); j -= incrMax)
            {
                p_data[j+incrMax] = p_data[j];
            }
            p_data[j+incrMax] = temp;
        }
        incrMax -= 2;
    }
}

/*!
* @brief Merging two sorted arrays
*
* @param[in] *p_data1 The input data array 1
* @param[in] *p_data2 The input data array 2
* @param[out] *p_result The merged result
* @param[in] dataSize1 The full size of data 1
* @param[in] dataSize2 The full size of data 2
* @param[out] *p_resultSize The full size of data 2
*
* @return void
*/
void MergingSortedArrays (int *p_data1, int *p_data2, int *p_result, size_t dataSize1, size_t dataSize2, int *p_resultSize)
{
    *p_resultSize = dataSize1 + dataSize2;

    int i = 0, j = 0, k = 0;
    while ( (i < dataSize1) && (j < dataSize2) )
    {
        p_result[k++] = (p_data1[i] < p_data2[j]) ? p_data1[i++] : p_data2[j++];
    }

    // Copy the remaining element
    while (i < dataSize1)
    {
        p_result[k++] = p_data1[i++];
    }

    while (j < dataSize2)
    {
        p_result[k++] = p_data2[j++];
    }
}

/*!
* @brief Merge sorting algorithm
*          Executes recursively
* @param[out] data The input data array
* @param[in] low Index of the lower sublist (Index of the 1st element at the beginning)
* @param[in] up Index of the upper sublist (Index of the last element at the beginning)
*
* @return void
*/
void MergeSort (int data[], int low, int up)
{
    if (low == up)      // Single element only
    {
        return;
    }

    int mid = (low + up) >> 1;
    int temp[100];
    MergeSort(data, low, mid);
    MergeSort(data, mid + 1, up);

    Merge(data, temp, low, mid, mid + 1, up);
    Copy(data, temp, low, up);
}

/*!
* @brief Heap sorting algorithm
*
* @param[out] *p_data The input data array
* @param[in] dataSize The full size of data
*
* @return void
*/
void HeapSort (int *p_data, size_t dataSize)
{
    if ( (NULL == p_data) || (0 == dataSize) )
    {
        perror("Invalid heap input.\n");
        return;
    }

    dataSize--;             // Must show the size of the heap
    Heapify(p_data, dataSize);
    while (dataSize > 0)
    {
        p_data[dataSize] = HeapDelete(p_data, &dataSize);
    }
}

/*!
* @brief Quick sorting algorithm
*
* @param[out] data[] The input data array
* @param[in] low Lower bound index
* @param[in] up Upper bound index
*
* @return void
*/
void QuickSort (int data[], int low, int up)
{
    if (low >= up)
    {
        return;
    }

    int pivotIndex = Partition (data, low, up);     // Calculate the pivot index
    QuickSort(data, low, pivotIndex - 1);       // Sort left sublist
    QuickSort(data, pivotIndex + 1, up);        // Sort right sublist
}


/*** EOF ***/

