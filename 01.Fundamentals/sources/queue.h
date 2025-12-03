/** @file queue.h
*
*   @brief Queue Header File.
*
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

// === Constant Definitions ===
//
#define QUEUE_EMPTY_DATA    -99999

// === Type Definitions ===
//
typedef struct queueType
{
    int *item;
    size_t qSize;
    int read;
    int write;
    bool isFull;
    bool isEmpty;
} queue_t;


// === Macros ===
//


// === Public API Functions ===
//
void InitQueue (queue_t *p_queue, size_t qSize);
void EnqueueData (queue_t *p_queue, int data);
int DequeueData (queue_t *p_queue);
bool GetQueueIsEmpty (queue_t *p_queue);
bool GetQueueIsFull (queue_t *p_queue);
size_t GetQueueElementSize (queue_t *p_queue);
void CleanupQueue (queue_t *p_queue);

#endif // QUEUE_H

/**** EOF ***/
