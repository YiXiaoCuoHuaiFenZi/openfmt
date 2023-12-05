/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_COMMENT_PARSER_H
#define OPENFMT_COMMENT_PARSER_H

#include "lib/linked_list.h"
#include "lib/g_list.h"
#include "lib/str_queue.h"
#include "proto.h"

PbCommentList* make_comments(GCharList* comments, PbPosition position);

void free_PbComment(PbCommentNode* ptr);

void free_GChar(GCharNode* ptr);

#endif //OPENFMT_COMMENT_PARSER_H
