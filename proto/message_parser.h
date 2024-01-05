/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse message.
**    Created Date:    2022-10-25
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_MESSAGE_PARSER_H
#define OPENFMT_MESSAGE_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"


PbMessage* make_pb_message(char* text, PbCommentList* comments);

void parse_message(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
);

#endif //OPENFMT_MESSAGE_PARSER_H
