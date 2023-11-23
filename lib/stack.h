/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_STACK_H
#define OPENFMT_STACK_H

#include <stdbool.h>

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

struct Node
{
	void* data;
	struct Node* next;
};

Stack create_stack();

void dispose_stack(Stack stack, void (* free_data_callback)(PtrToNode ptr_node));

Stack empty_stack(Stack stack);

bool is_empty_stack(Stack stack);

void push_stack(void* data, Stack stack);

void* top_stack(Stack stack, void (* free_data_callback)(PtrToNode ptr_node));

void pop_stack(Stack stack, void (* free_data_callback)(PtrToNode ptr_node));


#endif //OPENFMT_STACK_H
