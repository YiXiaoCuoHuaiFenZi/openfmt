/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Message, Enum, Service, Extend.
**    创建日期：    2022-11-14
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "comment_parser.h"
#include "detector.h"
#include "package_parser.h"
#include "option_parser.h"
#include "lib/str_queue.h"
#include "import_parser.h"
#include "message_parser.h"
#include "message_ele_parser.h"
#include "object_parser.h"
#include "enum_parser.h"
#include "service_parser.h"
#include "extend_parser.h"
#include "oneof_parser.h"
#include "enum_ele_parser.h"
#include "service_ele_parser.h"
#include "lib/g_hash_table.h"
#include "lib/str.h"
#include "lib/memory.h"

void append_as_bottom_comments(PbCommentList* comments, PbCommentList* bottom_comments)
{
	PbCommentNode* cur = bottom_comments->next;
	while (cur)
	{
		PbComment* pb_comment = cur->data;
		pb_comment->pos = BOTTOM;
		/*
		** create a total new comment data, and append it to the target comments list, so we can release bottom_comments
		** by calling dispose_linked_list.
		*/
		PbComment* new_comment = (PbComment*)malloc(sizeof(PbComment));
		memcpy(new_comment, pb_comment, sizeof(PbComment));
		new_comment->text = str_copy(pb_comment->text);
		// append the new comment data to the comments list.
		append_list(PbCommentNode, comments, new_comment);
		cur = cur->next;
	}
}

void update_current_obj_comments(State* state, PbCommentList* bottom_comments)
{
	if (strcmp(state->current_obj_type, "PbMessage") == 0)
	{
		PbMessage* current_obj = (PbMessage*)(state->current_obj);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(state->current_obj_type, "PbEnum") == 0)
	{
		PbEnum* current_obj = (PbEnum*)(state->current_obj);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(state->current_obj_type, "PbOneOf") == 0)
	{
		PbOneOf* current_obj = (PbOneOf*)(state->current_obj);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
	if (strcmp(state->current_obj_type, "PbExtend") == 0)
	{
		PbExtend* current_obj = (PbExtend*)(state->current_obj);
		append_as_bottom_comments(current_obj->comments, bottom_comments);
		return;
	}
}

char* get_parent_id(State* state)
{
	if (strcmp(state->current_obj_type, "PbMessage") == 0)
	{
		PbMessage* parent = (PbMessage*)(state->current_obj);
		return str_copy(parent->id);
	}
	if (strcmp(state->current_obj_type, "PbEnum") == 0)
	{
		PbEnum* parent = (PbEnum*)(state->current_obj);
		return str_copy(parent->id);
	}
	if (strcmp(state->current_obj_type, "PbOneOf") == 0)
	{
		PbOneOf* parent = (PbOneOf*)(state->current_obj);
		return str_copy(parent->id);
	}
	if (strcmp(state->current_obj_type, "PbExtend") == 0)
	{
		PbExtend* parent = (PbExtend*)(state->current_obj);
		return str_copy(parent->id);
	}

	return NULL;
}

List get_parent_elements(State* state)
{
	if (strcmp(state->current_obj_type, "PbMessage") == 0)
	{
		PbMessage* parent = (PbMessage*)(state->current_obj);
		return parent->elements;
	}
	if (strcmp(state->current_obj_type, "PbEnum") == 0)
	{
		PbEnum* parent = (PbEnum*)(state->current_obj);
		return parent->elements;
	}
	if (strcmp(state->current_obj_type, "PbOneOf") == 0)
	{
		PbOneOf* parent = (PbOneOf*)(state->current_obj);
		return parent->elements;
	}
	if (strcmp(state->current_obj_type, "PbExtend") == 0)
	{
		PbExtend* parent = (PbExtend*)(state->current_obj);
		return parent->elements;
	}

	return NULL;
}

ObjectInfo* get_parent_object_info(char* current_object_id, char* obj_type, State* state)
{
	ObjectInfo* r = (ObjectInfo*)g_malloc(sizeof(ObjectInfo));
	r->obj_id = NULL;
	r->obj_type = NULL;
	void* obj = g_hashtable_get(current_object_id, state->obj_dic);

	if (strcmp(obj_type, "PbMessage") == 0)
	{
		PbMessage* current_obj = (PbMessage*)obj;
		r->obj_id = current_obj->parent_id;
		r->obj_type = current_obj->parent_type;

		return r;
	}
	if (strcmp(obj_type, "PbEnum") == 0)
	{
		PbEnum* current_obj = (PbMessage*)obj;
		r->obj_id = current_obj->parent_id;
		r->obj_type = current_obj->parent_type;

		return r;
	}
	if (strcmp(obj_type, "PbOneOf") == 0)
	{
		PbOneOf* current_obj = (PbMessage*)obj;
		r->obj_id = current_obj->parent_id;
		r->obj_type = current_obj->parent_type;

		return r;


	}
	if (strcmp(obj_type, "PbExtend") == 0)
	{
		PbExtend* current_obj = (PbMessage*)obj;
		r->obj_id = current_obj->parent_id;
		r->obj_type = current_obj->parent_type;

		return r;
	}

	return r;
}

void current_obj_to_parent_obj(State* state)
{
	if (strcmp(state->current_obj_type, "PbMessage") == 0)
	{
		PbMessage* parent = (PbMessage*)(state->current_obj);
		state->parent_obj = parent;
		state->parent_obj_type = "PbMessage";
		return;
	}
	if (strcmp(state->current_obj_type, "PbEnum") == 0)
	{
		PbEnum* parent = (PbEnum*)(state->current_obj);
		state->parent_obj = parent;
		state->parent_obj_type = "PbEnum";
		return;
	}
	if (strcmp(state->current_obj_type, "PbOneOf") == 0)
	{
		PbOneOf* parent = (PbOneOf*)(state->current_obj);
		state->parent_obj = parent;
		state->parent_obj_type = "PbOneOf";
		return;
	}
	if (strcmp(state->current_obj_type, "PbExtend") == 0)
	{
		PbExtend* parent = (PbExtend*)(state->current_obj);
		state->parent_obj = parent;
		state->parent_obj_type = "PbExtend";
		return;
	}
}

void parent_obj_to_current_obj(State* state)
{
	if (state->parent_obj_type == NULL)
	{
		return;
	}

	if (strcmp(state->parent_obj_type, "PbMessage") == 0)
	{
		PbMessage* current_obj = (PbMessage*)(state->current_obj);
		if (current_obj->parent_id == NULL)
		{
			state->parent_obj_type = NULL;
		}
		else
		{
			state->current_obj = g_hashtable_get(current_obj->parent_id, state->obj_dic);
			state->current_obj_type = "PbMessage";

			ObjectInfo* info = get_parent_object_info(current_obj->id, current_obj->parent_type, state);
			state->parent_obj_type = info->obj_type;
		}
		return;
	}
	if (strcmp(state->parent_obj_type, "PbEnum") == 0)
	{
		PbEnum* current_obj = (PbEnum*)(state->current_obj);
		if (current_obj->parent_id == NULL)
		{
			state->parent_obj_type = NULL;
		}
		else
		{
			state->current_obj = g_hashtable_get(current_obj->parent_id, state->obj_dic);
			state->current_obj_type = "PbEnum";

			ObjectInfo* info = get_parent_object_info(current_obj->id, current_obj->parent_type, state);
			state->parent_obj_type = info->obj_type;
		}
		return;
	}
	if (strcmp(state->parent_obj_type, "PbOneOf") == 0)
	{
		PbOneOf* current_obj = (PbOneOf*)(state->current_obj);
		if (current_obj->parent_id == NULL)
		{
			state->parent_obj_type = NULL;
		}
		else
		{
			state->current_obj = g_hashtable_get(current_obj->parent_id, state->obj_dic);
			state->current_obj_type = "PbOneOf";

			ObjectInfo* info = get_parent_object_info(current_obj->id, current_obj->parent_type, state);
			state->parent_obj_type = info->obj_type;
		}
		return;
	}
	if (strcmp(state->parent_obj_type, "PbExtend") == 0)
	{
		PbExtend* current_obj = (PbExtend*)(state->current_obj);
		if (current_obj->parent_id == NULL)
		{
			state->parent_obj_type = NULL;
		}
		else
		{
			state->current_obj = g_hashtable_get(current_obj->parent_id, state->obj_dic);
			state->current_obj_type = "PbExtend";

			ObjectInfo* info = get_parent_object_info(current_obj->id, current_obj->parent_type, state);
			state->parent_obj_type = info->obj_type;
		}
		return;
	}
}

void parse_object(Protobuf* protobuf, SQueue line_queue, PbCommentList* top_comments, State* state)
{
	if (is_empty_str_queue(line_queue))
	{
		return;
	}

	if (top_comments == NULL)
	{
		top_comments = make_top_comments(line_queue);
	}

	char* line = str_copy(line_queue->head->str);
	char* tmp = trim(line);
	if (strstr(tmp, "}") && starts_with("}", tmp))
	{
		de_str_queue(line_queue);
		state->r_brace++;
		/*
		** There are comments exist at bottom of the message:
		** message Test {
		**     string header = 1;// header
		**     // message inner bottom
		**     //message inner bottom bottombottombottombottom
		** }
		**/
		if (top_comments != NULL)
		{
			update_current_obj_comments(state, top_comments);
			/*
			** the top_comments is bottom comments actually, and the comment value data will be added to the object,
			** so we must release this extra list data.
			*/
			free_comment_list(&top_comments);
		}

		if (state->l_brace == state->r_brace)
		{
			g_free(&tmp);
			g_free(&line);
			return;
		}

		if (state->parent_obj != NULL)
		{
			parent_obj_to_current_obj(state);
		}
	}
	g_free(&tmp);

	PbType pb_type = get_pb_type(line);

	switch (pb_type)
	{
	case Message:
	{
		PbMessage* obj = parse_pb_message(line, line_queue, top_comments);
		if (state->current_obj != NULL)
		{
			obj->parent_id = get_parent_id(state);
			append_linked_list(obj, "PbMessage", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(obj, "PbMessage", protobuf->objects);
		}
		state->l_brace++;
		state->current_obj = obj;
		state->current_obj_type = "PbMessage";
		g_hashtable_put(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
		break;
	}
	case Enum:
	{
		PbEnum* obj = parse_pb_enum(line, line_queue, top_comments);
		if (state->current_obj != NULL)
		{
			obj->parent_id = get_parent_id(state);
			append_linked_list(obj, "PbEnum", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(obj, "PbEnum", protobuf->objects);
		}
		state->l_brace++;
		state->current_obj = obj;
		state->current_obj_type = "PbEnum";
		g_hashtable_put(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
		break;
	}
	case Service:
	{
		PbService* obj = parse_pb_service(line, line_queue, top_comments);
		state->l_brace++;
		state->current_obj = obj;
		state->current_obj_type = "PbService";
		append_linked_list(obj, "PbService", protobuf->objects);
		break;
	}
	case Extend:
	{
		PbExtend* obj = parse_pb_extend(line, line_queue, top_comments);
		if (state->current_obj != NULL)
		{
			obj->parent_id = get_parent_id(state);
			append_linked_list(obj, "PbExtend", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(obj, "PbExtend", protobuf->objects);
		}
		state->l_brace++;
		state->current_obj = obj;
		state->current_obj_type = "PbExtend";
		g_hashtable_put(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
		break;
	}
	case OneOf:
	{
		PbOneOf* obj = parse_pb_oneof(line, line_queue, top_comments);
		if (state->current_obj != NULL)
		{
			obj->parent_id = get_parent_id(state);
			append_linked_list(obj, "PbOneOf", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}

		state->l_brace++;
		state->current_obj = obj;
		state->current_obj_type = "PbOneOf";
		break;
	}
		// The element of Message, OneOf and Extend has the same structure, so can be used by all of them.
	case MessageElement:
	{
		PbMessageElement* element = parse_pb_message_element(line, top_comments, line_queue);
		PbMessage* obj = (PbMessage*)(state->current_obj);
		append_linked_list(element, "PbMessageElement", obj->elements);
		break;
	}
	case EnumElement:
	{
		PbEnumElement* element = parse_pb_enum_element(line, top_comments, line_queue);
		PbEnum* obj = (PbEnum*)(state->current_obj);
		append_linked_list(element, "PbEnumElement", obj->elements);
		break;
	}
	case ServiceElement:
	{
		PbServiceElement* element = parse_pb_service_element(line, top_comments, line_queue);
		PbService* obj = (PbService*)(state->current_obj);
		append_linked_list(element, "PbServiceElement", obj->elements);
		break;
	}
	default:
	{
		break;
	}
	}
	g_free(&line);
	parse_object(protobuf, line_queue, NULL, state);
}