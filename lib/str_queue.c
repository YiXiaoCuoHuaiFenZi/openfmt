/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <stdio.h>
#include "str_queue.h"
#include "memory.h"

SQueue CreateSQueue()
{
    SQueue queue = (struct SQueueStruct *) g_malloc(sizeof(struct SQueueStruct));
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void DisposeSQueue(SQueue queue)
{
    PtrToSQueueNode currentNode = queue->head;
    while (currentNode != NULL)
    {
        PtrToSQueueNode nextNode = currentNode->next;
        g_free(&(currentNode->str));
        g_free(&currentNode);
        currentNode = nextNode;
    }
    queue->head = NULL;
    queue->rear = NULL;
    g_free(&queue);
}

bool IsEmptySQueue(SQueue queue)
{
    return queue->head == NULL;
}

void EnSQueue(char *str, SQueue queue)
{
    PtrToSQueueNode newNode = (struct SQueueNode *) g_malloc(sizeof(struct SQueueNode));
    newNode->str = str;
    newNode->next = NULL;
    if (IsEmptySQueue(queue))
    {
        queue->head = queue->rear = newNode;
    } else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void DeSQueue(SQueue queue)
{
    if (IsEmptySQueue(queue))
    {
        printf("%s", "SQueue is empty!");
    } else
    {
        PtrToSQueueNode frontNode = queue->head;
        queue->head = queue->head->next;
        if (queue->rear == frontNode)
        {
            queue->rear = NULL;
        }
        g_free(&(frontNode->str));
        g_free(&frontNode);
    }
}

char *SQueueFront(SQueue queue)
{
    if (IsEmptySQueue(queue))
    {
        printf("%s", "SQueue is empty!");
        return NULL;
    }

    return queue->head->str;
}

int SQueueSize(SQueue queue)
{
    if (IsEmptySQueue(queue))
    {
        return 0;
    }

    int size = 0;
    PtrToSQueueNode cur = queue->head;
    while (cur->next != NULL)
    {
        size++;
        cur = cur->next;
    }
    return size;
}