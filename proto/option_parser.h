/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-21
**    Updated Date:    2022-10-21
***********************************************************************************************************************/
#ifndef OPENFMT_OPTION_PARSER_H
#define OPENFMT_OPTION_PARSER_H

#include "proto.h"
#include "../lib/queue.h"

void parse_option(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf);

#endif //OPENFMT_OPTION_PARSER_H

