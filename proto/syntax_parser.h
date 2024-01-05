/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse syntax.
**    Created Date:    2022-10-07
**    Updated Date:    2022-10-07
***********************************************************************************************************************/
#ifndef OPENFMT_SYNTAX_PARSER_H
#define OPENFMT_SYNTAX_PARSER_H

#include "proto.h"
#include "../lib/queue.h"

void parse_syntax(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf);

#endif //OPENFMT_SYNTAX_PARSER_H
