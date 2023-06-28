/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse protobuf file to ADT(Abstract Data Type).
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_PROTO_PARSER_H
#define OPENFMT_PROTO_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"

Protobuf *parse(const char *file_path);

void parse_string_queue(Protobuf *protobuf, SQueue line_queue);

#endif //OPENFMT_PROTO_PARSER_H
