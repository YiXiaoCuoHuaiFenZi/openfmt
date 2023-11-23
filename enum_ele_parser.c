/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse element of enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "lib/str.h"
#include "comment_parser.h"
#include "enum_ele_parser.h"
#include "lib/memory.h"

PbEnumElement* make_pb_enum_element(char* text, PbCommentList* top_comments)
{
	//  to avoid impact the original line string, create a copy.
	char* s1 = str_copy(text);
	char* s2 = strtok(s1, "=");
	char* s3 = str_copy(s2);
	char* name = trim(s3);
	g_free(&s1);
	g_free(&s3);

	char* s4 = sub_str_between_str(text, "=", ";");
	char* number = trim(s4);
	g_free(&s4);

	PbEnumElement* ele = (PbEnumElement*)g_malloc(sizeof(PbEnumElement));
	ele->name = name;
	ele->number = number;
	ele->annotation = NULL;
	ele->comments = top_comments;

	// BAGGAGE_TYPE_CARRY_ON = 1[deprecated=true];//BAGGAGE_TYPE_CARRY_ON
	char* has_left_square_bracket = strstr(text, "[");
	char* has_right_square_bracket = strstr(text, "]");
	if (has_left_square_bracket && has_right_square_bracket)
	{
		// get the number value.
		char* ns = sub_str_between_str(text, "=", "[");
		g_free(&number);
		ele->number = trim(ns);
		g_free(&ns);

		// get the annotation value.
		char* s5 = sub_str_between_str(text, "[", "]");
		char* s6 = trim(s5);
		unsigned int size = strlen(s6) + 3; // '[', ']' and '\0'
		char* annotation = (char*)g_malloc(size);
		strcat(annotation, "[");
		strcat(annotation, s6);
		strcat(annotation, "]");
		annotation[size - 1] = '\0';
		ele->annotation = annotation;
		g_free(&s5);
		g_free(&s6);
	}

	return ele;
}