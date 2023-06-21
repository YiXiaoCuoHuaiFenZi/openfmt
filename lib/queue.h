/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2022-10-04
***********************************************************************************************************************/
#ifndef OPENFMT_QUEUE_H
#define OPENFMT_QUEUE_H

#include <stdbool.h>

struct QueueNode;
struct QueueStruct;
typedef struct QueueNode *PtrToQueueNode;
typedef struct QueueStruct *PtrToQueue;
typedef PtrToQueue Queue;

struct QueueNode
{
    void *data;
    struct QueueNode *next;
};

struct QueueStruct
{
    struct QueueNode *head;
    struct QueueNode *rear;
};

Queue CreateQueue();

void DisposeQueue(Queue queue, void (*FreeDataCallBack)(PtrToQueueNode queueNode));

bool IsEmptyQueue(Queue queue);

void Enqueue(void *data, Queue queue);

void Dequeue(Queue queue, void (*FreeDataCallBack)(PtrToQueueNode queueNode));

void *QueueFront(Queue queue);

int QueueSize(Queue queue);


#endif //OPENFMT_QUEUE_H
