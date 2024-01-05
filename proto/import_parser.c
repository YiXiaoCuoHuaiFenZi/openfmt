/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-24
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include "import_parser.h"
#include "package_parser.h"
#include <string.h>
#include "../lib/str.h"
#include "../lib/memory.h"
#include "common.h"
#include "comment_parser.h"
#include "../lib/os.h"

void parse_import(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
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

		PbImport* pb_import = (PbImport*)g_malloc(sizeof(PbImport));
		pb_import->value = value;
		pb_import->comments = comments;

		// parse line comment
		PbComment* line_comment = pick_up_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_import->comments, line_comment);
		}

		if (protobuf->imports == NULL)
		{
			protobuf->imports = create_list(PbImportNode);
		}
		append_list(PbImportNode, protobuf->imports, pb_import);
	}
}