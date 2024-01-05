/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-01
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include "linked_list.h"
#include "str.h"
#include "memory.h"
#include <string.h>

List create_linked_list()
{
	List list = (struct LinkedListNode*)g_malloc(sizeof(struct LinkedListNode));
	list->next = NULL;
	return list;
}

bool is_linked_list_last(Position position, List list)
{
	return position->next == NULL;
}

bool is_empty_linked_list(List list)
{
	return list->next == NULL;
}

void insert_linked_list(void* data, Position position, List list)
{
	Position temp_node;

	temp_node = g_malloc(sizeof(struct LinkedListNode));
	temp_node->data = data;
	temp_node->next = position->next;
	position->next = temp_node;
}

void append_linked_list(void* data, const char* data_type, List list)
{
	struct LinkedListNode* temp_node = (struct LinkedListNode*)g_malloc(sizeof(struct LinkedListNode));
	Position CurrentPosition = list;
	while (CurrentPosition->next != NULL)
	{
		CurrentPosition = CurrentPosition->next;
	}

	temp_node->data = data;
	temp_node->data_type = str_copy(data_type);
	temp_node->next = CurrentPosition->next;
	CurrentPosition->next = temp_node;
}

void dispose_linked_list(List list, void (* free_data_callback)(void* data))
{
	List head = list;

	list = list->next; // 跳过list head;
	while (list != NULL)
	{
		struct LinkedListNode* temp_node = list;
		list = list->next;
		free_data_callback(temp_node->data);
		g_free(to_void_ptr(&(temp_node->data_type)));
		g_free(to_void_ptr(&temp_node));
	}

	g_free(to_void_ptr(&head));
}
