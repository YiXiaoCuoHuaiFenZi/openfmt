/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse syntax.
**    Created Date:    2022-10-07
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "syntax_parser.h"
#include "common.h"
#include "comment_parser.h"
#include "../lib/os.h"
#include "../lib/memory.h"

void parse_syntax(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	if (proto_str[*index] != '=')
	{
		char message[100];
		char num_str[15];
		sprintf(num_str, "%lu", *index);
		strcat(message, "invalid symbol at ");
		strcat(message, num_str);
		strcat(message, " when parse syntax.\n");
		fail(message);
	}
	*index = *index + 1;

	char* s = pick_str_until(proto_str + *index, ';', false);
	if (s == NULL)
		fail("target char not found.");
	else
		*index = *index + strlen(s) + 1; // increase extra 1 to skip the ';' charactor.

	if (s != NULL)
	{
		char* value = trim(s);
		g_free(to_void_ptr(&s));

		PbSyntax* pb_syntax = (PbSyntax*)g_malloc(sizeof(PbSyntax));
		pb_syntax->value = value;
		pb_syntax->comments = comments;

		// parse line comment
		PbComment* line_comment = pick_up_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_syntax->comments, line_comment);
		}
		protobuf->syntax = pb_syntax;
	}
}
