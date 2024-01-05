/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse OneOf.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ONEOF_PARSER_H
#define OPENFMT_ONEOF_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbOneOf* make_pb_oneof(char* name, PbCommentList* comments);

void parse_oneof(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
);

#endif //OPENFMT_ONEOF_PARSER_H
