/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdio.h>
#include "queue.h"
#include "memory.h"

Queue create_queue()
{
    Queue queue = (struct QueueStruct *) g_malloc(sizeof(struct QueueStruct));
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void dispose_queue(Queue queue, void (*free_data_callback)(PtrToQueueNode queueNode))
{
    PtrToQueueNode cur = queue->head;
    while (cur != NULL)
    {
        PtrToQueueNode nextNode = cur->next;
        free_data_callback(cur);
        g_free(&cur);
        cur = nextNode;
    }
    queue->head = NULL;
    queue->rear = NULL;
    g_free(&queue);
}

bool is_empty_queue(Queue queue)
{
    return queue->head == NULL;
}

void en_queue(void *data, Queue queue)
{
    PtrToQueueNode new_node = (struct QueueNode *) g_malloc(sizeof(struct QueueNode));
    new_node->data = data;
    new_node->next = NULL;
    if (is_empty_queue(queue))
    {
        queue->head = queue->rear = new_node;
    } else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

void de_queue(Queue queue, void (*free_data_callback)(PtrToQueueNode queueNode))
{
    if (is_empty_queue(queue))
    {
        printf("%s", "Queue is empty!");
    } else
    {
        PtrToQueueNode front_node = queue->head;
        queue->head = queue->head->next;
        free_data_callback(front_node);
        //g_free(&frontNode);
    }
}

void *queue_front(Queue queue)
{
    if (is_empty_queue(queue))
    {
        printf("%s", "Queue is empty!");
        return NULL;
    }

    return queue->head->data;
}

int queue_size(Queue queue)
{
    if (is_empty_queue(queue))
    {
        return 0;
    }

    int size = 0;
    PtrToQueueNode cur = queue->head;
    while (cur->next != NULL)
    {
        size++;
        cur = cur->next;
    }
    return size;
}