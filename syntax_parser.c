/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse syntax.
**    创建日期：    2022-10-07
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "syntax_parser.h"
#include "lib/str.h"
#include "lib/memory.h"
#include "lib/os.h"
#include "comment_parser.h"

void parse_syntax(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	if (proto_str[*index] != '=')
	{
		char message[100];
		char num_str[15];
		sprintf(num_str, "%d", *index);
		strcat(message, "invalid symbol at ");
		strcat(message, num_str);
		strcat(message, " when parse syntax.\n");
		fail(message);
	}
	*index = *index + 1;
	char* s = get_str_until(proto_str, index, ';', false);
	if (s != NULL)
	{
		char* value = trim(s);
		g_free(&s);

		PbSyntax* pb_syntax = (PbSyntax*)g_malloc(sizeof(PbSyntax));
		pb_syntax->value = value;
		pb_syntax->comments = comments;

		// 解析单行注释
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_syntax->comments, single_line_comment);
		}
		protobuf->syntax = pb_syntax;
	}
}
