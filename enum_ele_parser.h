/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse element of enum.
**    创建日期：    2022-11-15
**    更新日期：    2022-11-15
***********************************************************************************************************************/
#ifndef OPENFMT_ENUM_ELE_PARSER_H
#define OPENFMT_ENUM_ELE_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

PbEnumElement *parse_pb_enum_element(char *line, PbCommentList *topComments, SQueue lineQueue);

#endif //OPENFMT_ENUM_ELE_PARSER_H
