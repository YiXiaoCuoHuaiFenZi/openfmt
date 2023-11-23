/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Message, Enum, Service, Extend.
**    创建日期：    2022-11-14
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_OBJECT_PARSER_H
#define OPENFMT_OBJECT_PARSER_H

#include "proto.h"
#include "lib/str_queue.h"
#include "lib/g_hash_table.h"

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

void append_as_bottom_comments(PbCommentList* comments, PbCommentList* bottom_comments);

void update_current_obj_comments(State* state, PbCommentList* bottom_comments);

void parent_obj_to_current_obj(State* state);

char* get_parent_id(State* state);

List get_parent_elements(State* state);

void current_obj_to_parent_obj(State* state);

ObjectInfo* get_parent_object_info(char* object_id, char* obj_type, State* state);

#endif //OPENFMT_OBJECT_PARSER_H
