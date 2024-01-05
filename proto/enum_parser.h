/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse enum.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_PARSER_H
#define OPENFMT_ENUM_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbEnum* make_pb_enum(char* name, PbCommentList* comments);

void parse_pb_enum(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
);

#endif //OPENFMT_ENUM_PARSER_H
