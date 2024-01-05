/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-04
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_QUEUE_H
#define OPENFMT_QUEUE_H

#include <stdbool.h>

struct QueueNode;
struct QueueStruct;
typedef struct QueueNode* PtrToQueueNode;
typedef struct QueueStruct* PtrToQueue;
typedef PtrToQueue Queue;

struct QueueNode
{
	void* data;
	struct QueueNode* next;
};

struct QueueStruct
{
	struct QueueNode* head;
	struct QueueNode* rear;
};

Queue create_queue();

void dispose_queue(Queue queue, void (* free_data_callback)(PtrToQueueNode queueNode));

bool is_empty_queue(Queue queue);

void en_queue(void* data, Queue queue);

void de_queue(Queue queue, void (* free_data_callback)(PtrToQueueNode queueNode));

void* queue_front(Queue queue);

int queue_size(Queue queue);


#endif //OPENFMT_QUEUE_H
