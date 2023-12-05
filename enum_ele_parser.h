/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse element of enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_ELE_PARSER_H
#define OPENFMT_ENUM_ELE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbEnumElement* make_pb_enum_element(char* line, PbCommentList* top_comments);

#endif //OPENFMT_ENUM_ELE_PARSER_H
