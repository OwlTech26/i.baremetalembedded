/**
 * Copyright (c) 2022 iSee
 *
 * \file main.c
 * \brief Fundamental Data Structures & Algorithms using C language. https://www.udemy.com/course/data-structures-stack-queue-linkedlist/learn/lecture/13610766?start=0#overview
 * 		  Data Structures and Algorithms In C. https://www.udemy.com/course/data-structures-and-algorithms-in-c/learn/lecture/7937012?start=0#overview
 * \author iSee
 * \date 11.10.2022
 */

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//#define RUN_FUNDAMENTALS_2
#ifndef RUN_FUNDAMENTALS_2
	#include "ui.h"
#else
	#include "callback.h"
	#include "linked_list_2.h"
	#include "queue_2.h"
	#include "recursion_2.h"
	#include "tricks.h"
#endif // RUN_FUNDAMENTALS_2


/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#ifndef RUN_FUNDAMENTALS_2
	#define FUNDAMENTALS_1_TEST_EN 			   0
#else
	#define FUNDAMENTALS_2_QUEUE_EN			   1
	#define FUNDAMENTALS_2_CALLBACK_EN         1
	#define FUNDAMENTALS_2_LINKED_LIST_EN      1
	#define FUNDAMENTALS_2_TRICKS_EN           1
	#define FUNDAMENTALS_2_RECURSION_EN        1
#endif // RUN_FUNDAMENTALS_2


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
#ifndef RUN_FUNDAMENTALS_2
/** \brief Implements Fundamental Data Structures & Algorithms using C language.
 *  \param
 *  \return Status
 */
static inline int main_fundamental_1(void);

#else
/** \brief Implements Data Structures and Algorithms In C.
 *  \param 
 *  \return Status
 */
static inline int main_fundamental_2(void);
#endif // RUN_FUNDAMENTALS_2

/******************************************************************************/
/*--------------------------Local Function Prototypes-------------------------*/
/******************************************************************************/
#ifndef RUN_FUNDAMENTALS_2
/** \brief Finished Execution Status
 *  \param 
 *  \return 
 *  	\retval 
 */
static void FinishedStatus(void);
#endif // RUN_FUNDAMENTALS_2

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
#ifndef RUN_FUNDAMENTALS_2
/** \brief Implements Fundamental Data Structures & Algorithms using C language.*/
static inline int main_fundamental_1(void)
{
#   if FUNDAMENTALS_1_TEST_EN
    TestQueue(0);
    TestBinarySearch(0);
    TestRecursion(0);
    TestBinarySearchTree(0);
    TestMorse(0);
    TestHeap(0);
    TestSorting(0);
#   else
	MenuInit();

	int select = 8;
	const int exit = 0;

	MenuPrint(exit);

	// scanf("%d", &select);

	select = tolower(select);
	MenuUI(&select, exit);
	fflush(stdin);

	atexit(FinishedStatus);
#   endif // FUNDAMENTALS_1_TEST_EN

	return 0;
}

#else
/** \brief Implements Data Structures and Algorithms In C.*/
static inline int main_fundamental_2(void)
{
//=== Queue ===
#if FUNDAMENTALS_2_QUEUE_EN
    int front;
    int rear;
    int *p_queue = InitializeQueue(&front, &rear, QUEUE_SIZE);
    printf("%d, %d: %d", front, rear, QUEUE_SIZE);

#endif // FUNDAMENTALS_2_QUEUE_EN

//=== Callback ===
#if FUNDAMENTALS_2_CALLBACK_EN

#if 1
    printf("%d\n", Callback(&add, 9, 5));
    printf("%d\n", Callback(&subtract, 9, 5));
    printf("%d\n", Callback(&multiply, 9, 5));
#endif // 0
    function_t *call[3] = {(function_t *)add(9, 5), (function_t *)subtract(9, 5), (function_t *)multiply(9, 5)};
    for (int i = 0; i < NUM_OF(call); i++)
    {
        printf("%d\n", (int)call[i]);
    }

#endif // FUNDAMENTALS_2_CALLBACK_EN

//=== Linked List ===
#if FUNDAMENTALS_2_LINKED_LIST_EN
    atexit(ExitLinkedList);

    nodeData_t agent = {"Andrea Parker", 7};
    node_t *p_root = CreateRoot(agent);

    nodeData_t agent2 = {"Nadine Kruger", 4};
    PushList(p_root, agent2);

    nodeData_t agent3 = {"Verona Feldbush", 9};
    PushList(p_root, agent3);

    nodeData_t agent4 = {"Gemma Arteron", 6};
    PushList(p_root, agent4);
    PrintList_2(p_root);
    PopList(p_root);
    puts("");
    PrintList_2(p_root);
    PushListRootBefore(&p_root, agent4);
    puts("");
    PrintList_2(p_root);
    nodeData_t agent5 = {"Karen Vodermann", 5};
    InsertListAfter(p_root, agent5, 3);
    puts("");
    PrintList_2(p_root);
    puts("");
    CleanList(&p_root);
    puts("");
    PrintList_2(p_root);
#endif // FUNDAMENTALS_2_LINKED_LIST_EN

// === Tricks ===
#if FUNDAMENTALS_2_TRICKS_EN
    atexit(ExitTricks);
    testNumOf_t testNumLUT[] =
    {
        { 12, 15, "Test1" },
        { 4, 5, "Test2"   },
        { 56, 91, "Test3" },
        { 15, 45, "Test4" }
    };

    testNumOf_t *p_testNum = testNumLUT;
    int testNumSize = NUM_OF(testNumLUT);
    printf("Size: %d\n", testNumSize);

    for (int i = 0; i < testNumSize; i++)
    {
        printf("%2d %2d %s\n", (p_testNum + i)->a, (p_testNum + i)->b, (p_testNum + i)->name);
    }

    SWAP(p_testNum[2].a, p_testNum[2].b);
    printf("-----\n%2d %2d %s\n", p_testNum[2].a, p_testNum[2].b, p_testNum[2].name);

    GoesTo(10);

    int matrix[3][3] = {
		#include "initMatrix.txt"
    };

    puts("\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%2d, ", matrix[i][j]);
        }
        puts("");
    }

    int sorting[] =
    {
        #include "sorting.txt"
    };

    puts("\n");
    for (int i = 0; i < NUM_OF(sorting); i++)
    {
        printf("%d, ", sorting[i]);
    }
    BubbleSort_2(sorting, NUM_OF(sorting));
    puts("");
    for (int i = 0; i < NUM_OF(sorting); i++)
    {
        printf("%d, ", sorting[i]);
    }
    puts("\n--- Binary File Access ---");
    FILE *p_file = fopen("data.bin", "wb");
    if (NULL == p_file)
    {
        perror("Unable to create binary file.\n");
        return -1;
    }

    binaryData_t binData;
    for (int i = 0; i < 5; i++)
    {
        binData.a = 3*i + 15;
        binData.b = i * 2;
        fwrite(&binData, sizeof(binaryData_t), 1, p_file);
    }
    fclose(p_file);

    FILE *p_fileRead = fopen("data.bin", "rb");
    if (NULL == p_fileRead)
    {
        perror("Unable to create binary file.\n");
        return -1;
    }

    binaryData_t binDataRead;
    for (int i = 0; i < 5; i++)
    {
        fread(&binDataRead, sizeof(binDataRead), 1, p_fileRead);
        printf("%d. %d, %d\n", (i + 1), binDataRead.a, binDataRead.b);
    }
    fclose(p_fileRead);

    // Pointer To Array And Array Of Pointers
    int *p_arr1[5];     // Array of 5 integer pointers
    int (*p_arr2)[5];   // Pointer to an array of 5 integers
    int * (p_arr3[5]);  // Same as p_arr1

#endif // FUNDAMENTALS_2_TRICKS_EN

// === Recursion ===
#if FUNDAMENTALS_2_RECURSION_EN
    printf("Factorial: %d\n", Factorial_2(4));
    printf("Fibonacci: %d\n", Fibonacci(10));
    printf("Power of 10 integer: %u\n", Pow10Int(3));
    printf("Bitwise addition: %d", BitwiseAdd(11, 7));
#endif // FUNDAMENTALS_2_RECURSION_EN

    return 0;
}
#endif // RUN_FUNDAMENTALS_2

/******************************************************************************/
/*----------------------Local Function Implementations------------------------*/
/******************************************************************************/
#ifndef RUN_FUNDAMENTALS_2
/** \brief */
static void FinishedStatus(void)
{
    puts("\n\n=== Execution is Finished ===");
}
#endif // RUN_FUNDAMENTALS_2

/******************************************************************************/
/*-----------------------------------MAIN-------------------------------------*/
/******************************************************************************/
/** \brief
 *  \param
 *  \return
 *  	\retval
 */
int main (int argv, char **argc)
{
	printf("======================================\n");
	printf("| C Fundamentals and Data Structures |\n");
	printf("======================================\n");
	puts("");

#ifndef RUN_FUNDAMENTALS_2
	return main_fundamental_1();
#else
	return main_fundamental_2();
#endif // RUN_FUNDAMENTALS_2
}

/*** EOF ***/
