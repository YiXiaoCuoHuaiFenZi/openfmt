/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2023-12-06
**    Updated Date:    2023-12-06
***********************************************************************************************************************/
#ifndef OPENFMT_COMMON_H
#define OPENFMT_COMMON_H

#include <string.h>
#include "../lib/str.h"
#include "../lib/str_queue.h"
#include "../lib/g_hash_table.h"
#include "proto.h"

typedef enum
{
	start,
	line_comment,
	block_comment_start,
	syntax,
	package,
	option,
	import,
	extend,
	message,
	message_element,
	extend_element,
	proto_enum,
	enum_element,
	service,
	service_element,
	one_of,
	invalid_key_word
} Status;

bool is_new_line(char c);

void skip_spaces(const char* str, unsigned long* index);

#endif //OPENFMT_COMMON_H
