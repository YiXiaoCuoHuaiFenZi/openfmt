/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "message_parser.h"
#include "lib/memory.h"

PbMessage *parse_pb_message(char *line, SQueue line_queue, PbCommentList *comments)
{
    char *s = sub_str_between_str(line, "message", "{");
    char *name = trim(s);
    g_free(&s);

    PbMessage *obj = (PbMessage *) g_malloc(sizeof(PbMessage));
    UUID *uuid = uuid4();
    obj->id = str_copy(uuid->hex);
    obj->parent_id = NULL;
    obj->name = name;
    obj->comments = comments;
    obj->elements = create_linked_list();
    PbComment *pb_comment = parse_comment(line);
    if (pb_comment != NULL)
    {
        append_list(PbCommentNode, obj->comments, pb_comment);
    }
    de_str_queue(line_queue);
    free_uuid4(uuid);
    return obj;
}

PbMessage *new_parse_pb_message(char *name, PbCommentList *comments)
{
//	char *s = sub_str_between_str(text, "message", "{");
//	char *name = trim(s);
//	g_free(&s);

	PbMessage *obj = (PbMessage *) g_malloc(sizeof(PbMessage));
	UUID *uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->parent_type = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();
//	PbComment *pb_comment = parse_comment(text);
//	if (pb_comment != NULL)
//	{
//		append_list(PbCommentNode, obj->comments, pb_comment);
//	}
	free_uuid4(uuid);
	return obj;
}