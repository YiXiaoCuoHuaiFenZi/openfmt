/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-21
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include "comment_parser.h"
#include "package_parser.h"
#include "common.h"
#include "../lib/memory.h"
#include "../lib/os.h"


void parse_package(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	char* s = pick_str_until(proto_str + *index, ';', false);
	if (s == NULL)
		fail("target char not found.");
	else
		*index = *index + strlen(s) + 1; // increase extra 1 to skip the ';' charactor.

	if (s != NULL)
	{
		char* value = trim(s);
		g_free(to_void_ptr(&s));

		PbPackage* pb_package = (PbPackage*)g_malloc(sizeof(PbPackage));
		pb_package->value = value;
		pb_package->comments = comments;

		// parse line comment
		PbComment* line_comment = pick_up_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_package->comments, line_comment);
		}
		protobuf->package = pb_package;
	}
}