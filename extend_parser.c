/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Extend.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "extend_parser.h"
#include "lib/memory.h"

PbMessage* make_pb_extend(char* name, PbCommentList* comments)
{
	PbExtend* obj = (PbExtend*)g_malloc(sizeof(PbExtend));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->parent_type = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();

	free_uuid4(uuid);
	return obj;
}
