/** @file queue.c
*
*   @brief Queue implementations.
*
*/
#include <stdio.h>

#include "queue.h"

// === Private Functions ===
//

// === Public Function API ===
//
/*!
*  @brief Initialize Queue
*
*  @param[in] *p_queue Pointer to the queue
*  @param[in] qSize Size of the queue
*
*  @return void
*/
void InitQueue (queue_t *p_queue, size_t qSize)
{
    p_queue->item = (int *) calloc(qSize, sizeof(int));
    if (NULL == p_queue->item)
    {
        perror("Unable to allocate queue elemnets.\n");
        return;
    }
    p_queue->qSize = qSize;
    p_queue->read = 0;
    p_queue->write = 0;
    p_queue->isEmpty = true;
    p_queue->isFull = false;
}

/*!
*  @brief Inserting Element to the Queue
*
*  @param[in] *p_queue Pointer to the queue
*  @param[in] data The input data
*
*  @return void
*/
void EnqueueData (queue_t *p_queue, int data)
{
    if (p_queue->isFull)        // Check the queue is full status
    {
        return;
    }

    p_queue->item[p_queue->write] = data;
    p_queue->isEmpty = false;

    if (++p_queue->write == p_queue->qSize)
    {
        p_queue->write = 0;
    }

    if (p_queue->write == p_queue->read)
    {
        p_queue->isFull = true;
    }
}

/*!
*  @brief Removing Element from the Queue
*
*  @param[in] *p_queue Pointer to the queue
*
*  @return The output data
*/
int DequeueData (queue_t *p_queue)
{
    if (p_queue->isEmpty)       // Check queue is empty status
    {
        return QUEUE_EMPTY_DATA;
    }

    int data = 0;

    data = p_queue->item[p_queue->read];
    p_queue->isFull = false;

    if (++p_queue->read == p_queue->qSize)
    {
        p_queue->read = 0;
    }

    if (p_queue->read == p_queue->write)
    {
        p_queue->isEmpty = true;
    }

    return data;
}

/*!
*  @brief Queries the Empty Status of the Queue
*
*  @param[in] *p_queue Pointer to the queue
*
*  @return TRUE: empty, FALSE: not empty
*/
bool GetQueueIsEmpty (queue_t *p_queue)
{
    return p_queue->isEmpty;
}

/*!
*  @brief Queries the Full Status of the Queue
*
*  @param[in] *p_queue Pointer to the queue
*
*  @return TRUE: full, FALSE: not full
*/
bool GetQueueIsFull (queue_t *p_queue)
{
    return p_queue->isFull;
}

/*!
*  @brief Queries the Number of the Elements in the Queue
*
*  @param[in] *p_queue Pointer to the queue
*
*  @return The number of queue elements
*/
size_t GetQueueElementSize (queue_t *p_queue)
{
    if (p_queue->isEmpty)
    {
        return 0;
    }
    if (p_queue->isFull)
    {
        return p_queue->qSize;
    }
    return abs(p_queue->write - p_queue->read);
}

/*!
*  @brief Deallocates Queue Items
*
*  @param[in] *p_queue Pointer to the queue
*
*  @return void
*/
void CleanupQueue (queue_t *p_queue)
{
    free(p_queue->item);
}

/**** EOF ***/

