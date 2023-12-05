/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_MESSAGE_PARSER_H
#define OPENFMT_MESSAGE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "proto_parser.h"


PbMessage* make_pb_message(char* text, PbCommentList* comments);

void parse_message(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		State* state,
		Protobuf* protobuf
);

#endif //OPENFMT_MESSAGE_PARSER_H
