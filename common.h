/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-12-06
**    更新日期：    2023-12-06
***********************************************************************************************************************/
#ifndef OPENFMT_COMMON_H
#define OPENFMT_COMMON_H

#include <string.h>
#include "lib/str.h"
#include "lib/str_queue.h"
#include "lib/g_hash_table.h"
#include "proto.h"

typedef enum
{
	start,
	line_comment,   // '/'
	block_comment_start,
	comment,
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


struct StateStructure;
typedef struct StateStructure State;

struct StateStructure
{
	unsigned short l_brace;
	unsigned short r_brace;
	void* current_obj;
	char* current_obj_type;
	void* parent_obj;
	char* parent_obj_type;
	PbCommentList* comments;
	GHashTable* obj_dic;
};

struct ObjectInfoStructure;
typedef struct ObjectInfoStructure ObjectInfo;
struct ObjectInfoStructure
{
	char* obj_id;
	char* obj_type;
};

bool is_new_line(char c);

void skip_spaces(const char* str, unsigned long* index);

char* get_str_until(const char* str, unsigned long* index, char ch, bool include);

char* pick_str_until(const char* str, unsigned long* index, char ch, bool include);

#endif //OPENFMT_COMMON_H
