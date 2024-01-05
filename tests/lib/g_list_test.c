/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-28
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "../macro.h"
#include "g_list_test.h"
#include "../../lib/memory.h"

int test_G_NodeTemplate_int()
{
	GIntList l;
	int a[] = { 1, 2 };
	int* i = a;
	l.data = i;
	l.next = NULL;

	return TEST_SUCCESS;
}

int test_G_NodeTemplate_char()
{
	GCharList l;
	char* ch = "aaa";
	l.data = ch;
	l.next = NULL;

	return TEST_SUCCESS;
}

int test_create_linked_list()
{
	GIntList* l = create_list(GIntNode);
	if (l->next != NULL)
		return TEST_FAIL;

	if (l->data != NULL)
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_append_list()
{
	GCharList* l = create_list(GCharNode);
	char* ch = (char*)g_malloc(sizeof(char) * 5);
	strcpy(ch, "aaaa");
	append_list(GCharNode, l, ch);

	if (strcmp(l->next->data, "aaaa") != 0)
		return TEST_FAIL;

	if (l->next->next != NULL)
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_is_empty_list()
{
	GCharList* l = create_list(GCharNode);
	if (!is_empty_list(l))
		return TEST_FAIL;

	char* ch = (char*)g_malloc(sizeof(char) * 5);
	strcpy(ch, "aaaa");
	append_list(GCharNode, l, ch);

	if (is_empty_list(l))
		return TEST_FAIL;

	return TEST_SUCCESS;
}

int test_dispose_list()
{
	GCharList* l0 = create_list(GCharNode);
	dispose_list(GCharNode, l0, free_char_test);
	if (l0 != NULL)
		return TEST_FAIL;

	GCharList* l1 = create_list(GCharNode);
	char* ch1 = (char*)g_malloc(sizeof(char) * 5);
	strcpy(ch1, "aaaa");
	append_list(GCharNode, l1, ch1);

	char* ch2 = (char*)g_malloc(sizeof(char) * 5);
	strcpy(ch2, "bbbb");
	append_list(GCharNode, l1, ch2);

	dispose_list(GCharNode, l1, free_char_test);

	if (l1 != NULL)
		return TEST_FAIL;

	if (l1 != NULL)
		return TEST_FAIL;

	return TEST_SUCCESS;
}

void free_char_test(GCharNode* ptr)
{
	char* t = ptr->data;
	g_free(to_void_ptr(&t));
}
