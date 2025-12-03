/** @file test.c
*
* @brief Simple Test Procedures
*
*/

#include "test.h"

// === Protected Functions ===
//
/*!
* @brief Array data copy
*
* @param[in] *p_source The data to be copied
* @param[out] *p_target The data where to be copied
* @param[in] dataSize The size of both arrays
*
* @return void
*/
static void CopySortingData (const int *p_source, int * const p_target, size_t dataSize)
{
    if ( (0 == dataSize) || (NULL == p_source) || (NULL == p_target) )
    {
        perror("Invalid input array.\n");
        return;
    }

    for (int i = 0; i < dataSize; ++i)
    {
        p_target[i] = p_source[i];
    }
}

// === Public API Functions ===
//
/*!
* @brief Simple Queue Functionality Test
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestQueue (int x)
{
    queue_t q1;
    InitQueue(&q1, 5);

    EnqueueData(&q1, 4);
    EnqueueData(&q1, 3);
    EnqueueData(&q1, 8);
    EnqueueData(&q1, -5);
    EnqueueData(&q1, -9);
    EnqueueData(&q1, -11);

    puts("-- 1. --");
    for (int i = 0; i < 6; ++i)
    {
        printf("%d. %d\n", q1.read, DequeueData(&q1));
    }

    printf("Elements in the queue: %d\n", GetQueueElementSize(&q1));
    EnqueueData(&q1, 46);
    EnqueueData(&q1, 52);
    EnqueueData(&q1, 300);
    printf("Elements in the queue: %d\n", GetQueueElementSize(&q1));
    EnqueueData(&q1, -146);
    EnqueueData(&q1, -54);
    EnqueueData(&q1, -111);
    printf("Elements in the queue: %d\n", GetQueueElementSize(&q1));

    puts("-- 2. --");
    for (int i = 0; i < 6; ++i)
    {
        if (!GetQueueIsEmpty(&q1))
        {
            printf("%d. %d\n", q1.read, DequeueData(&q1));
        }
    }

    CleanupQueue(&q1);

    return 0;
}

/*!
* @brief Simple Binary Search Tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestBinarySearch (int x)
{
    list_t binList;
    InitializeList(&binList);

    srand(time(NULL));

    for (int i = 0; i < 11; ++i)
    {
        InsertListItem(&binList, rand());
    }

    int listData[20];

    PrintList(&binList, listData, false);
    for (int i = 0; i < binList.listSize; ++i)
    {
        printf("%d, ", listData[i]);
    }

    printf("\nDeleted item: %d, Size: %d\n", DeleteListItem(&binList, 5), binList.listSize);
    printf("\nDeleted item: %d, Size: %d\n", DeleteListItem(&binList, 1), binList.listSize);
    printf("\nDeleted item: %d, Size: %d\n", DeleteListItem(&binList, binList.listSize), binList.listSize);

    PrintList(&binList, listData, false);
    for (int i = 0; i < binList.listSize; ++i)
    {
        printf("%d, ", listData[i]);
    }

    CleanUpList(&binList);

    puts("\n----------- O ---------------------\n");
    InitializeList(&binList);

    for (int i = 0; i < 12; ++i)
    {
        InsertListItem(&binList, i*i);
    }

    PrintList(&binList, listData, false);
    for (int i = 1; i <= binList.listSize; ++i)
    {
        printf("%3d. ", i);
    }
    puts("");
    for (int i = 0; i < binList.listSize; ++i)
    {
        printf("%3d, ", listData[i]);
    }

    int data = 49;
    printf("\n  -> Binary search (%d): %d", data, BinarySearch(&binList, data));

    CleanUpList(&binList);

    return 0;
}

/*!
* @brief Simple Recursion Tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestRecursion (int x)
{
    PrintHello(3);
    JugglerSequence(3);
    puts("");
    printf("%d\n", Factorial(5));

    puts("---- O ----\nRecursive Binary Search");
    int data[12];
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%3d. ", i);
    }

    puts("");
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        data[i] = i*i;
        printf("%3d, ", data[i]);
    }

    int item = 36;
    printf("\nSearch (%d): %d\n", item, RecursiveBinarySearch(data, 0, NUM_OF(data) - 1, item));
    puts("---- O ----\nRecursive Decimal to Binary Converter");

    char result[33] = {'\0'};
    for (int i = 0; i < 32; ++i)
    {
        printf("Decimal (%d) to Binary: ", i);
        RecursiveDecimalToBinary(i, result);
        printf("%s\n", result);
        result[0] = '\0';
    }

    return 0;
}

/*!
* @brief Binary Search Tree Tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestBinarySearchTree (int x)
{
    const int keys[] = {10, 25, 4, 20, 2, 8, 35, 15, 22};
    treeNode_t *p_root = NULL;

    CreateBinSearchTree(&p_root, keys, NUM_OF(keys));

    captureType_t data;
    InitCapture(&data, NUM_OF(keys));
    InorderTraversal(p_root, &data);

    if (data.b_overFlow)
    {
        perror("Captured data is overflow.\n");
    }

    puts("Inorder traversal:");
    for (int i = 0; i < data.captureLimit; ++i)
    {
        printf("%d, ", data.key[i]);
    }

    puts("\n\nPreorder traversal:");
    ResetCapture(&data);
    PreorderTraversal(p_root, &data);
    for (int i = 0; i < data.captureLimit; ++i)
    {
        printf("%d, ", data.key[i]);
    }

    puts("\n\nPostorder traversal:");
    ResetCapture(&data);
    PostorderTraversal(p_root, &data);
    for (int i = 0; i < data.captureLimit; ++i)
    {
        printf("%d, ", data.key[i]);
    }

    treeNode_t *p_find;
    char buffer[11] = {'\0'};
    puts("\n\nBinary search in the binary tree:");
    for (int i = 0; i < data.captureLimit; ++i)
    {
        p_find = BinaryTreeSearch(p_root, data.key[i]);
        if (NULL == p_find)
        {
            strcpy(buffer, "NOT FOUND");
        }
        else
        {
            snprintf(buffer, NUM_OF(buffer), "%d", p_find->key);
        }
        printf("Data %d in the list: %s\n", data.key[i], buffer);

        p_find = BinaryTreeSearch(p_root, i);
        if (NULL == p_find)
        {
            strcpy(buffer, "NOT FOUND");
        }
        else
        {
            snprintf(buffer, NUM_OF(buffer), "%d", p_find->key);
        }
        printf("Data %d in the list: %s\n", i, buffer);
    }

    CleanupCapture(&data);
    DestroyTree(p_root);

    return 0;
}

/*!
* @brief Morse encoder / decoder tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestMorse (int x)
{
    char buffer[BUFFER_SIZE] = {'\0'};
    char source[] = "Hello World! -2020-?.";
    EncodeMorse(source, buffer, BUFFER_SIZE);
    printf("\n%s\n%s\n", source, buffer);

    morse_t *p_morseTree = NULL;
    BuildMorseTree(&p_morseTree);

    printf("%c %c\n", p_morseTree->dash->key, p_morseTree->dot->key);
    printf("%c %c %c %c\n", p_morseTree->dash->dash->key, p_morseTree->dash->dot->key, p_morseTree->dot->dash->key, p_morseTree->dot->dot->key);
    printf("%c %c %c %c %c %c %c %c\n", p_morseTree->dash->dash->dash->key, p_morseTree->dash->dash->dot->key, p_morseTree->dash->dot->dash->key, p_morseTree->dash->dot->dot->key,
                                        p_morseTree->dot->dash->dash->key, p_morseTree->dot->dash->dot->key, p_morseTree->dot->dot->dash->key, p_morseTree->dot->dot->dot->key);
    puts("\n");
    MorseTreePostorderTraversal(p_morseTree);

    char actual;
    char expected;
    for (int i = 0; i < NUM_OF(MORSE_LUT); ++i)
    {
        actual = DecodeMorseKey(MORSE_LUT[i], p_morseTree);
        expected = (i < ALPHA_NUM)                                       ? (char) i + 'a' :
                   ( (i >= ALPHA_NUM) && (i < (ALPHA_NUM + DIGIT_NUM)) ) ? (char) (i - ALPHA_NUM) + '0' :
                   (i == (ALPHA_NUM + DIGIT_NUM))                        ? '?' :
                   (i == (ALPHA_NUM + DIGIT_NUM + 1))                    ? '.' : '-';
        printf("%5s %c ?= %c => %s\n", MORSE_LUT[i], actual, expected, (actual == expected) ? "PASS" : "FAIL");
    }

    MorseTreeDestroy(p_morseTree);

    return 0;
}

/*!
* @brief Heap sorting tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestHeap(int x)
{
    const int dataTest[] = {0, 25, 40, 50, 80, 65, 70, 45, 20, 30};
    int data[NUM_OF(dataTest)];

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nHeap Sort:");
    HeapSort(data, NUM_OF(data));
    for (int i = 1; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    int bigData[1000] = {0};

    srand(time(NULL));
    for (int i = 1; i < NUM_OF(bigData); ++i)
    {
        bigData[i] = rand() % 10000 + 1;
    }


    puts("\n\nSorted bigger data:");
    HeapSort(bigData, NUM_OF(bigData));
    for (int i = 1; i < NUM_OF(bigData); ++i)
    {
        printf("%d, ", bigData[i]);
    }

    return 0;
}

/*!
* @brief Other sorting algorithm tester
*
* @param[in] x Dummy data
*
* @return 0
*/
int TestSorting(int x)
{
    const int dataTest[] = {0, 25, 40, 50, 80, 65, 70, 45, 20, 30};
    const int dataTest2[] = {15, 20, 18, 33, 4, 8, 1};
    int data[NUM_OF(dataTest)];
    int data2[NUM_OF(dataTest2)];

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\nInitial data: ");
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    puts("\n\nSelection Sorting:");
    SelectionSort(data, NUM_OF(data));
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nBubble Sorting:");
    BubbleSort(data, NUM_OF(data));
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nInsertion Sorting:");
    InsertionSort(data, NUM_OF(data));
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nShell Sorting:");
    ShellSort(data, NUM_OF(data), 5);
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    CopySortingData(dataTest2, data2, NUM_OF(dataTest2));
    puts("\n\nMerging Sorted Arrays:");
    BubbleSort(data, NUM_OF(data));
    BubbleSort(data2, NUM_OF(data2));
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }
    puts("");
    for (int i = 0; i < NUM_OF(data2); ++i)
    {
        printf("%d, ", data2[i]);
    }
    int result[NUM_OF(data) + NUM_OF(data2)];
    int resultSize;
    MergingSortedArrays(data, data2, result, NUM_OF(data), NUM_OF(data2), &resultSize);
    puts("");
    for (int i = 0; i < resultSize; ++i)
    {
        printf("%d, ", result[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nMerge Sorting:");
    MergeSort(data, 0, NUM_OF(data) - 1);
    for (int i = 0; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    CopySortingData(dataTest, data, NUM_OF(dataTest));
    puts("\n\nQuick Sort:");
    QuickSort(data, 0, NUM_OF(data) - 1);
    for (int i = 1; i < NUM_OF(data); ++i)
    {
        printf("%d, ", data[i]);
    }

    return 0;
}

/*** EOF ***/


