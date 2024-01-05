/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-24
**    Updated Date:    2022-10-24
***********************************************************************************************************************/
#ifndef OPENFMT_IMPORT_PARSER_H
#define OPENFMT_IMPORT_PARSER_H

#include "proto.h"

void parse_import(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf);

#endif //OPENFMT_IMPORT_PARSER_H

