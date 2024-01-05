/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-21
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "option_parser.h"
#include "common.h"
#include "comment_parser.h"
#include "../lib/memory.h"
#include "../lib/os.h"

void parse_option(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	PbOption* pb_option = (PbOption*)g_malloc(sizeof(PbOption));
	char* s0 = pick_str_until(proto_str + *index, '=', false);
	if (s0 == NULL)
		fail("target char not found.");
	else
		*index = *index + strlen(s0) + 1; // increase extra 1 to skip the '=' charactor.

	if (s0 != NULL)
	{
		char* name = trim(s0);
		g_free(to_void_ptr(&s0));
		pb_option->name = name;
	}

	char* s1 = pick_str_until(proto_str + *index, ';', false);
	if (s1 == NULL)
		fail("target char not found.");
	else
		*index = *index + strlen(s1) + 1; // increase extra 1 to skip the ';' charactor.

	if (s1 != NULL)
	{
		char* value = trim(s1);
		g_free(to_void_ptr(&s1));
		pb_option->value = value;
	}

	pb_option->comments = comments;

	// parse line comment
	PbComment* line_comment = pick_up_line_comment(proto_str, index);
	if (line_comment != NULL)
	{
		append_list(PbCommentNode, pb_option->comments, line_comment);
	}

	if (protobuf->options == NULL)
	{
		protobuf->options = create_list(PbOptionNode);
	}
	append_list(PbOptionNode, protobuf->options, pb_option);
}