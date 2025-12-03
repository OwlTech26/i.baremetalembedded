/** @file ui.c
*
* @brief Command Prompt Unit Interface
*
*/

#include "ui.h"

// === Global Variables by Module ===
//
static callback_t processRegister;

// === Protected Functions ===
//
/*!
* @brief Initializes the process register for function callbacks.
*
* @return void
*/
static inline void InitializeCallback (void)
{
    processRegister.index = -1;
    processRegister.call[0] = NULL;
}

/*!
* @brief Gets the number of registered callbacks
*
* @return The number of registered callbacks
*/
static inline int GetNumOfCallback (void)
{
    return (processRegister.index + 1);
}

/*!
* @brief Registers the current callback
*
* @param[in] *p_callback The input callback
*
* @return void
*/
static void RegisterCallback (api_t p_callback)
{
    if (processRegister.index >= (CALLBACK_LIMIT - 1))
    {
        perror("Unable to add new process to the callback collection.\n");
        return;
    }

    processRegister.index++;
    processRegister.call[processRegister.index] = p_callback;
}

/*!
* @brief Executes the registered process at the specified index
*
* @param[in] index
*
* @return void
*/
static int ExecuteProcess (int index, int x)
{
    if ( (index > processRegister.index) || (index < 0) )
    {
        perror("Process index is out of range.\n");
        return -1;
    }

    return processRegister.call[index](x);
}

// === Public API Functions ===
//
/*!
* @brief Initializing menu callbacks
*
* @return void
*/
void MenuInit (void)
{
    InitializeCallback();
    RegisterCallback(&PrintToBinary);
    RegisterCallback(&ReverseText);
    RegisterCallback(&BracketCheck);
    RegisterCallback(&InfixToPostfix);
    RegisterCallback(&TestQueue);
    RegisterCallback(&TestBinarySearch);
    RegisterCallback(&TestBinarySearchTree);
    RegisterCallback(&TestMorse);
    RegisterCallback(&TestHeap);
    RegisterCallback(&TestSorting);
}

/*!
* @brief Prints the available menu selections
*
* @param[in] exit The exit character
*
* @return void
*/
void MenuPrint (const int exit)
{
    int list = 1;
    puts("\n\n=== Select from Menu ===");
    printf("%d. Print Number Binary\n", list++);
    printf("%d. Reverse Text\n", list++);
    printf("%d. Paranthesis Checker\n", list++);
    printf("%d. Infix to Postfix Converter\n", list++);
    printf("%d. Test the Queue\n", list++);
    printf("%d. Test the Binary Search\n", list++);
    printf("%d. Test Binary Tree with Binary Search\n", list++);
    printf("%d. Test Morse Encoder and Decoder\n", list++);
    printf("%d. Test Heap\n", list++);
    printf("%d. Test Sorting Algorithms\n", list++);
    puts("   ---");
    printf("   Exit (%d): ", exit);
}

/*!
* @brief Menu display
*
* @param[in] *p_input The selection input
* @param[in] exit The exit character
*
* @return void
*/
void MenuUI (int *p_select, const int exit)
{
    if (*p_select == exit)
    {
        puts("Exiting...");
        return;
    }

    if (*p_select > GetNumOfCallback())
    {
        puts("Nothing was selected from the list.");
        return;
    }

    printf("Selected: %d.\n", *p_select);
    ExecuteProcess(*p_select - 1, 8965);
}

/*** EOF ***/
