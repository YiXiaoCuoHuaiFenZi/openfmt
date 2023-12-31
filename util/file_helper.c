/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-09-30
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "file_helper.h"
#include "../lib/memory.h"

List read_line_to_list(const char* file_path)
{
	FILE* fp;
	char* des_line = NULL;
	size_t len = 0;
	size_t read = 0;

	fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		printf("could not open file: %s", file_path);
		return NULL;
	}

	List list = create_linked_list();
	while ((read = getline(&des_line, &len, fp)) != -1)
	{
		char* line = (char*)g_malloc(strlen(des_line) + 1);
		strcpy(line, des_line);
		append_linked_list(line, "char", list);
	}

	fclose(fp);
	g_free(to_void_ptr(&des_line));

	return list;
}

void print_line_list(List lines)
{
	PtrToLinkedListNode ptr_node = lines->next;
	while (ptr_node)
	{
		char* line = (char*)ptr_node->data;
		printf("%s", line);
		ptr_node = ptr_node->next;
	}
}

SQueue read_line_to_str_queue(const char* file_path)
{
	FILE* fp;
	char* des_line = NULL;
	size_t len = 0;
	size_t read = 0;

	fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		printf("could not open file: %s", file_path);
		return NULL;
	}

	SQueue lines = create_str_queue();
	while ((read = getline(&des_line, &len, fp)) != -1)
	{
		char* line = (char*)g_malloc(strlen(des_line) + 1);
		strcpy(line, des_line);
		en_str_queue(line, lines);
	}

	fclose(fp);
	g_free(to_void_ptr(&des_line));

	return lines;
}

void print_str_queue(SQueue line_queue)
{
	PtrToSQueueNode currentNode = line_queue->head;
	while (currentNode)
	{
		printf("%s", currentNode->str);
		currentNode = currentNode->next;
	}
}

char* read_file(const char* file_path)
{
	FILE* fp;
	long length;
	char* content = NULL;

	fp = fopen(file_path, "rb");
	if (fp == NULL)
	{
		printf("could not open file: %s", file_path);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	content = g_malloc(length + 1);
	fread(content, 1, length, fp);
	content[length] = '\0';
	fclose(fp);

	return content;
}