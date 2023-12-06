/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-04
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdio.h>
#include "str_queue.h"
#include "memory.h"

SQueue create_str_queue()
{
	SQueue queue = (struct SQueueStruct*)g_malloc(sizeof(struct SQueueStruct));
	queue->head = NULL;
	queue->rear = NULL;
	return queue;
}

void dispose_str_queue(SQueue queue)
{
	PtrToSQueueNode cur = queue->head;
	while (cur != NULL)
	{
		PtrToSQueueNode next = cur->next;
		g_free(to_void_ptr(&(cur->str)));
		g_free(to_void_ptr(&cur));
		cur = next;
	}
	queue->head = NULL;
	queue->rear = NULL;
	g_free(to_void_ptr(&queue));
}

bool is_empty_str_queue(SQueue queue)
{
	return queue->head == NULL;
}

void en_str_queue(char* str, SQueue queue)
{
	PtrToSQueueNode new_node = (struct SQueueNode*)g_malloc(sizeof(struct SQueueNode));
	new_node->str = str;
	new_node->next = NULL;
	if (is_empty_str_queue(queue))
	{
		queue->head = queue->rear = new_node;
	}
	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
}

void de_str_queue(SQueue queue)
{
	if (is_empty_str_queue(queue))
	{
		printf("%s", "SQueue is empty!");
	}
	else
	{
		PtrToSQueueNode front_node = queue->head;
		queue->head = queue->head->next;
		if (queue->rear == front_node)
		{
			queue->rear = NULL;
		}
		g_free(to_void_ptr(&(front_node->str)));
		g_free(to_void_ptr(&front_node));
	}
}

char* str_queue_front(SQueue queue)
{
	if (is_empty_str_queue(queue))
	{
		printf("%s", "SQueue is empty!");
		return NULL;
	}

	return queue->head->str;
}

int str_queue_size(SQueue queue)
{
	if (is_empty_str_queue(queue))
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