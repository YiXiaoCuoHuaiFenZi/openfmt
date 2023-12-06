/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message element.
**    创建日期：    2022-11-11
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "common.h"
#include "comment_parser.h"
#include "message_ele_parser.h"
#include "lib/str.h"
#include "lib/memory.h"

PbMessageElement* make_pb_message_element(char* text, PbCommentList* top_comments)
{
	PbMessageElement* pb_message_element = NULL;
	char* s0 = strstr(text, "map<");
	if (s0)
	{
		pb_message_element = make_map_message_element(text, top_comments);
	}
	else
	{
		pb_message_element = make_common_message_element(text, top_comments);
	}

	return pb_message_element;
}

PbMessageElement* make_message_element(
		char* label,
		char* type,
		char* name,
		char* number,
		char* annotation,
		PbCommentList* comments
)
{
	PbMessageElement* pb_message_element = (PbMessageElement*)g_malloc(sizeof(PbMessageElement));
	pb_message_element->label = label;
	pb_message_element->type = type;
	pb_message_element->name = name;
	pb_message_element->number = number;
	pb_message_element->annotation = annotation;
	pb_message_element->comments = comments;

	return pb_message_element;
}

PbMessageElement* make_map_message_element(char* text, PbCommentList* top_comments)
{
	//  map<string,       Project> projects = 3; // map field comment d
	char* s1 = sub_str_between_str(text, "<", ",");
	char* map_type = trim(s1);

	char* s2 = sub_str_between_str(text, ",", ">");
	char* map_value = trim(s2);

	char* s3 = sub_str_between_str(text, ">", "=");
	char* name = trim(s3);

	char* s4 = sub_str_between_str(text, "=", ";");
	char* number = trim(s4);

	unsigned int size = strlen("map<") + strlen(map_type) + strlen(", ") + strlen(map_value) + strlen(">") + 1;
	char* type = g_malloc(size);
	strcat(type, "map<");
	strcat(type, map_type);
	strcat(type, ", ");
	strcat(type, map_value);
	strcat(type, ">");
	type[size - 1] = '\0';

	PbMessageElement* pb_message_element = make_message_element(NULL, type, name, number, NULL, top_comments);

	g_free(to_void_ptr(&s1));
	g_free(to_void_ptr(&map_type));
	g_free(to_void_ptr(&s2));
	g_free(to_void_ptr(&map_value));
	g_free(to_void_ptr(&s3));
	g_free(to_void_ptr(&s4));

	return pb_message_element;
}

PbMessageElement* make_common_message_element(char* text, PbCommentList* top_comments)
{
	// common.RequestContext  request_context = 1;            // Basic request context data
	//  char *s1 = strtok(line, ";");
	//  to avoid impact the original line string, create a copy.
	char* line_copy = str_copy(text);
	char* s2 = strtok(line_copy, "=");

	char* parts[5] = { NULL };
	int index = 0;
	char* token = strtok(s2, " ");
	while (token != NULL)
	{
		parts[index] = str_copy(token);
		index++;
		token = strtok(NULL, " ");
	}
	g_free(to_void_ptr(&line_copy));

	int valid_value_count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (parts[i])
		{
			valid_value_count++;
		}
	}

	char* label = NULL;
	char* type = NULL;
	char* name = NULL;
	char* number = NULL;
	char* annotation = NULL;
	if (valid_value_count == 2)
	{
		type = parts[0];
		name = parts[1];
	}

	if (valid_value_count == 3)
	{
		label = parts[0];
		type = parts[1];
		name = parts[2];
	}

	char* s3 = sub_str_between_str(text, "=", ";");
	number = trim(s3);
	g_free(to_void_ptr(&s3));

	// string market = 1 [(validate.rules).string.len = 2]; // The traveller
	char* has_left_square_bracket = strstr(text, "[");
	char* has_right_square_bracket = strstr(text, "]");
	if (has_left_square_bracket && has_right_square_bracket)
	{
		// get the number value.
		char* s4 = sub_str_between_str(text, "=", "[");
		g_free(to_void_ptr(&number));
		number = trim(s4);
		g_free(to_void_ptr(&s4));

		// get the annotation value.
		char* s5 = sub_str_between_str(text, "[",
				";");  //  the annotation maybe contains ']' so not get the value by "[" and "]"
		char* s6 = trim(s5);
		unsigned int size = strlen(s6) + 2; // '[', and '\0'
		annotation = (char*)g_malloc(size);
		strcat(annotation, "[");
		strcat(annotation, s6);
		// strcat(annotation, "]");
		annotation[size - 1] = '\0';
		g_free(to_void_ptr(&s5));
		g_free(to_void_ptr(&s6));
	}

	PbMessageElement* pb_message_element = make_message_element(label, type, name, number, annotation, top_comments);

	return pb_message_element;
}

void parse_message_element(const char* proto_str, unsigned long* index, PbCommentList* comments, State* state)
{
	char* text = get_str_until(proto_str, index, ';', true);
	PbMessageElement* pb_message_element = make_pb_message_element(text, comments);
	// 解析单行注释
	PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
	if (single_line_comment != NULL)
	{
		append_list(PbCommentNode, pb_message_element->comments, single_line_comment);
	}
	PbMessage* obj = (PbMessage*)(state->current_obj);
	append_linked_list(pb_message_element, "PbMessageElement", obj->elements);

	g_free(to_void_ptr(&text));

}