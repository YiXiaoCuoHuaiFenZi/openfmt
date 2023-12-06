/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-12-06
**    更新日期：    2023-12-06
***********************************************************************************************************************/
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "lib/memory.h"
#include "lib/os.h"

bool is_new_line(char c)
{
	return (c == '\r' || c == '\n');
}

void skip_spaces(const char* str, unsigned long* index)
{
	char ch = str[*index];
	while (ch != '\0')
	{
		if (!isspace(ch))
		{
			break;
		}
		*index = *index + 1;
		ch = str[*index];
	}
}

char* get_str_until(const char* str, unsigned long* index, char ch, bool include)
{
	char cur_ch = str[*index];
	int len = 0;
	bool found = false;
	while (cur_ch != '\0')
	{
		if (cur_ch == ch)
		{
			found = true;
			break;
		}
		cur_ch = str[*index + len];
		len++;
	}
	if (found)
	{

		char* r = (char*)g_malloc(len + 1);
		if (include)
		{
			memcpy(r, str + *index, len);
			r[len] = '\0';
		}
		else
		{
			memcpy(r, str + *index, len - 1);
			r[len - 1] = '\0';
		}
		*index = *index + len;
		return r;
	}
	fail("target char not found.");
	return NULL;
}

char* pick_str_until(const char* str, unsigned long* index, char ch, bool include)
{
	char cur_ch = str[*index];
	int len = 1;
	bool found = false;
	while (cur_ch != '\0')
	{
		if (cur_ch == ch)
		{
			found = true;
			break;
		}
		cur_ch = str[*index + len];
		len++;
	}
	if (found)
	{

		char* r = (char*)g_malloc(len + 1);
		if (include)
		{
			memcpy(r, str + *index, len);
			r[len] = '\0';
		}
		else
		{
			memcpy(r, str + *index, len - 1);
			r[len - 1] = '\0';
		}
//		*index = *index + len;
		return r;
	}
	fail("target char not found.");
	return NULL;
}
