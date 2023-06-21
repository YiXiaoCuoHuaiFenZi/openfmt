/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2022-10-25
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "message_parser.h"
#include "lib/memory.h"

PbMessage *parse_pb_message(char *line, SQueue lineQueue, PbCommentList *comments)
{
    char *s = sub_str_between_str(line, "message", "{");
    char *name = trim(s);
    g_free(&s);

    PbMessage *obj = (PbMessage *) g_malloc(sizeof(PbMessage));
    UUID *uuid = uuid4();
    obj->id = str_copy(uuid->hex);
    obj->parentId = NULL;
    obj->name = name;
    obj->comments = comments;
    obj->elements = CreateList();
    PbComment *pbComment = parse_comment(line);
    if (pbComment != NULL)
    {
        append_list(PbCommentNode, obj->comments, pbComment);
    }
    DeSQueue(lineQueue);
    free_uuid4(uuid);
    return obj;
}