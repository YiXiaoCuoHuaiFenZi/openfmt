/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse element of enum.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_ELE_PARSER_H
#define OPENFMT_ENUM_ELE_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbEnumElement* make_pb_enum_element(char* line, PbCommentList* top_comments);

void parse_pb_enum_element(const char* proto_str, unsigned long* index, PbCommentList* comments, Stack object_stack);

#endif //OPENFMT_ENUM_ELE_PARSER_H
