/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <stdio.h>
#include "queue.h"
#include "memory.h"

Queue CreateQueue()
{
    Queue queue = (struct QueueStruct *) g_malloc(sizeof(struct QueueStruct));
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void DisposeQueue(Queue queue, void (*FreeDataCallBack)(PtrToQueueNode queueNode))
{
    PtrToQueueNode currentNode = queue->head;
    while (currentNode != NULL)
    {
        PtrToQueueNode nextNode = currentNode->next;
        FreeDataCallBack(currentNode);
        g_free(&currentNode);
        currentNode = nextNode;
    }
    queue->head = NULL;
    queue->rear = NULL;
    g_free(&queue);
}

bool IsEmptyQueue(Queue queue)
{
    return queue->head == NULL;
}

void Enqueue(void *data, Queue queue)
{
    PtrToQueueNode newNode = (struct QueueNode *) g_malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (IsEmptyQueue(queue))
    {
        queue->head = queue->rear = newNode;
    } else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void Dequeue(Queue queue, void (*FreeDataCallBack)(PtrToQueueNode queueNode))
{
    if (IsEmptyQueue(queue))
    {
        printf("%s", "Queue is empty!");
    } else
    {
        PtrToQueueNode frontNode = queue->head;
        queue->head = queue->head->next;
        FreeDataCallBack(frontNode);
        //g_free(&frontNode);
    }
}

void *QueueFront(Queue queue)
{
    if (IsEmptyQueue(queue))
    {
        printf("%s", "Queue is empty!");
        return NULL;
    }

    return queue->head->data;
}

int QueueSize(Queue queue)
{
    if (IsEmptyQueue(queue))
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