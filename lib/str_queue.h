/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-04
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_SQUEUE_H
#define OPENFMT_SQUEUE_H

#include <stdbool.h>

struct SQueueNode;
struct SQueueStruct;
typedef struct SQueueNode* PtrToSQueueNode;
typedef struct SQueueStruct* PtrToSQueue;
typedef PtrToSQueue SQueue;

struct SQueueNode
{
	char* str;
	struct SQueueNode* next;
};

struct SQueueStruct
{
	struct SQueueNode* head;
	struct SQueueNode* rear;
};

SQueue create_str_queue();

void dispose_str_queue(SQueue queue);

bool is_empty_str_queue(SQueue queue);

void en_str_queue(char* str, SQueue queue);

void de_str_queue(SQueue queue);

char* str_queue_front(SQueue queue);

int str_queue_size(SQueue queue);


#endif //OPENFMT_SQUEUE_H
