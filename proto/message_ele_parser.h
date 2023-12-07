/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-11-11
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_MESSAGE_ELE_PARSER_H
#define OPENFMT_MESSAGE_ELE_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbMessageElement* make_pb_message_element(char* text, PbCommentList* top_comments);

PbMessageElement* make_message_element(
		char* label,
		char* type,
		char* name,
		char* number,
		char* annotation,
		PbCommentList* comments
);

PbMessageElement* make_map_message_element(char* line, PbCommentList* top_comments);

PbMessageElement* make_common_message_element(char* line, PbCommentList* top_comments);

void parse_message_element(const char* proto_str, unsigned long* index, PbCommentList* comments, Stack object_stack);

#endif //OPENFMT_MESSAGE_ELE_PARSER_H

