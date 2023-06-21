/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Extend.
**    创建日期：    2022-11-15
**    更新日期：    2022-11-15
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "extend_parser.h"
#include "lib/memory.h"

PbExtend *parse_pb_extend(char *line, SQueue lineQueue, PbCommentList *comments)
{
    char *s = sub_str_between_str(line, "extend", "{");
    char *name = trim(s);
    g_free(&s);

    PbExtend *obj = (PbExtend *) g_malloc(sizeof(PbExtend));
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
