/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_STACK_H
#define OPENFMT_STACK_H

#include <stdbool.h>

struct StackNode;
typedef struct StackNode* PtrToStackNode;
typedef PtrToStackNode Stack;

struct StackNode
{
	void* data;
	char* data_type;
	struct StackNode* next;
};

Stack create_stack();

void dispose_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node));

Stack empty_stack(Stack stack);

bool is_empty_stack(Stack stack);

void push_stack(void* data, char* data_type, Stack stack);

PtrToStackNode top_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node));

void pop_stack(Stack stack, void (* free_data_callback)(PtrToStackNode ptr_node));


#endif //OPENFMT_STACK_H
