/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse Extend.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_EXTEND_PARSER_H
#define OPENFMT_EXTEND_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbExtend* make_pb_extend(char* name, PbCommentList* comments);

void parse_extend(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
);

#endif //OPENFMT_EXTEND_PARSER_H
