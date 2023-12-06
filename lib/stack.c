/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "memory.h"

Stack create_stack()
{
	Stack stack = (struct Node*)g_malloc(sizeof(struct Node));
	stack->next = NULL;
	return stack;
}

bool is_empty_stack(Stack stack)
{
	return stack->next == NULL;
}

void pop_stack(Stack stack, void (* free_data_callback)(PtrToNode ptr_node))
{
	if (is_empty_stack(stack))
	{
		printf("%s", "Empty stack!");
	}
	else
	{
		PtrToNode first_node = stack->next;
		stack->next = stack->next->next;
		free_data_callback(first_node->data);
		g_free(to_void_ptr(&first_node));
	}
}

void push_stack(void* data, Stack stack)
{
	PtrToNode ptr_node = (struct Node*)g_malloc(sizeof(struct Node));
	ptr_node->data = data;
	ptr_node->next = stack->next;
	stack->next = ptr_node;
}

void* top_stack(Stack stack, void (* free_data_callback)(PtrToNode ptr_node))
{
	if (!is_empty_stack(stack))
	{
		return stack->next->data;
	}
	printf("%s", "Empty stack!");
	exit(-1);
}
