
/** @file queue.c
*
*   @brief Circular queue implementation
*
*/

#include "queue_2.h"

int *InitializeQueue (int *p_front, int *p_rear, size_t qSize)
{
    int *queue = (int *) calloc(qSize, sizeof(int));

    if (NULL == queue)
    {
        perror("Unable to initialize queue.\n");
        return NULL;
    }

    *p_front = -1;
    *p_rear = -1;

    return queue;
}

/*** EOF ***/
