/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse OneOf.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "oneof_parser.h"
#include "lib/memory.h"

PbOneOf* make_pb_oneof(char* name, PbCommentList* comments)
{

	PbOneOf* obj = (PbOneOf*)g_malloc(sizeof(PbOneOf));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();
	free_uuid4(uuid);
	return obj;
}