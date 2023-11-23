/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "lib/str.h"
#include "option_parser.h"
#include "lib/memory.h"

PbOption* parse_option(char* line)
{
	// get option name
	char* s1 = sub_str_between_str(line, "option", "=");
	char* name = trim(s1);

	// get option value
	char* s2 = sub_str_between_str(line, "=", ";");
	char* value = trim(s2);

	g_free(&s1);
	g_free(&s2);

	PbOption* pb_option = (PbOption*)g_malloc(sizeof(PbOption));
	pb_option->name = name;
	pb_option->value = value;
	pb_option->comments = NULL;

	return pb_option;
}