/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse service element.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_SERVICE_ELE_PARSER_H
#define OPENFMT_SERVICE_ELE_PARSER_H

#include "proto.h"
#include "../lib/str_queue.h"
#include "proto_parser.h"

PbServiceElement* make_pb_service_element(char* text, PbCommentList* top_comments);

void parse_pb_service_element(const char* proto_str, unsigned long* index, PbCommentList* comments, Stack object_stack);

#endif //OPENFMT_SERVICE_ELE_PARSER_H
