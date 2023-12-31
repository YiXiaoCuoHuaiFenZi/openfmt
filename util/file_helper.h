/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-09-30
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_FILE_HELPER_H
#define OPENFMT_FILE_HELPER_H

#include "../lib/linked_list.h"
#include "../lib/str_queue.h"

List read_line_to_list(const char* file_path);

void print_line_list(List lines);

SQueue read_line_to_str_queue(const char* file_path);

void print_str_queue(SQueue line_queue);

char* read_file(const char* file_path);

#endif //OPENFMT_FILE_HELPER_H
