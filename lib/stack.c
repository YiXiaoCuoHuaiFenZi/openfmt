/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Methods to handle generic stack.
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "memory.h"

Stack create_stack()
{
	Stack stack = (struct StackNode*)g_malloc(sizeof(struct StackNode));
	stack->next = NULL;
	return stack;
}

bool is_empty_stack(Stack stack)
{
	return stack->next == NULL;
}

void pop_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node))
{
	if (is_empty_stack(stack))
	{
		printf("%s", "Empty stack!");
	}
	else
	{
		PtrToStackNode first_node = stack->next;
		stack->next = stack->next->next;
		if (free_data_callback != NULL)
			free_data_callback(first_node->data);
		g_free(to_void_ptr(&first_node));
	}
}

void push_stack(void* data, char* data_type, Stack stack)
{
	PtrToStackNode ptr_node = (struct StackNode*)g_malloc(sizeof(struct StackNode));
	ptr_node->data = data;
	ptr_node->data_type = data_type;
	ptr_node->next = stack->next;
	stack->next = ptr_node;
}

PtrToStackNode top_stack(Stack stack)
{
	if (!is_empty_stack(stack))
	{
		return stack->next;
	}
	printf("%s", "Empty stack!");
	exit(-1);
}

void dispose_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node))
{
	printf("not implemented method dispose_stack.");
	exit(1);
}
