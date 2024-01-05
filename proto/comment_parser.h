/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_COMMENT_PARSER_H
#define OPENFMT_COMMENT_PARSER_H

#include "../lib/linked_list.h"
#include "../lib/g_list.h"
#include "../lib/str_queue.h"
#include "proto.h"

PbCommentList* make_comments(GCharList* comments, PbPosition position);

void free_PbComment(PbCommentNode* ptr);

void free_GChar(GCharNode* ptr);

char* clean_comment_str(const char* comment);

PbComment* pick_up_line_comment(const char* proto_str, unsigned long* index);

char* pick_up_comment_str(const char* proto_str, unsigned long* index);

GCharList* pick_up_all_comments(const char* proto_str, unsigned long* index);

#endif //OPENFMT_COMMENT_PARSER_H
