/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2022-10-04
***********************************************************************************************************************/
#ifndef OPENFMT_SQUEUE_H
#define OPENFMT_SQUEUE_H

#include <stdbool.h>

struct SQueueNode;
struct SQueueStruct;
typedef struct SQueueNode *PtrToSQueueNode;
typedef struct SQueueStruct *PtrToSQueue;
typedef PtrToSQueue SQueue;

struct SQueueNode
{
    char *str;
    struct SQueueNode *next;
};

struct SQueueStruct
{
    struct SQueueNode *head;
    struct SQueueNode *rear;
};

SQueue CreateSQueue();

void DisposeSQueue(SQueue queue);

bool IsEmptySQueue(SQueue queue);

void EnSQueue(char *str, SQueue queue);

void DeSQueue(SQueue queue);

char *SQueueFront(SQueue queue);

int SQueueSize(SQueue queue);


#endif //OPENFMT_SQUEUE_H
