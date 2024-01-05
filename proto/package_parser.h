/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-21
**    Updated Date:    2022-10-21
***********************************************************************************************************************/
#ifndef OPENFMT_PACKAGE_PARSER_H
#define OPENFMT_PACKAGE_PARSER_H

#endif //OPENFMT_PACKAGE_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"

void parse_package(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf);