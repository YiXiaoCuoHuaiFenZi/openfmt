/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse service element.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "common.h"
#include "comment_parser.h"
#include "service_ele_parser.h"
#include "../lib/memory.h"

PbServiceElement* make_pb_service_element(char* text, PbCommentList* top_comments)
{
	//  to avoid impact the original line string, create a copy.
	char* s0 = str_copy(text);
	char* s1 = sub_str_between_str(s0, "rpc ", ";");
	char* s2 = replace("(", "", s1);
	char* s3 = replace(")", "", s2);
	g_free(to_void_ptr(&s0));
	g_free(to_void_ptr(&s1));
	g_free(to_void_ptr(&s2));

	char* parts[4] = { NULL };
	int index = 0;
	char* token = strtok(s3, " ");
	while (token != NULL)
	{
		parts[index] = str_copy(token);
		index++;
		token = strtok(NULL, " ");
	}
	g_free(to_void_ptr(&s3));

	PbServiceElement* ele = (PbServiceElement*)g_malloc(sizeof(PbServiceElement));

	ele->label = g_malloc(4);   /* why not use ele->label = "rpc"; because String literals are stored in such a  */
	strcpy(ele->label, "rpc");       /* way that they're available for the lifetime of the program.                   */
	ele->label[3] = '\0';
	ele->name = parts[0];
	ele->request = parts[1];
	ele->response = parts[3];
	ele->comments = top_comments;
	g_free(to_void_ptr(&(parts[2]))); // release resource of string "returns"

	return ele;
}

void parse_pb_service_element(const char* proto_str, unsigned long* index, PbCommentList* comments, Stack object_stack)
{
	char* text = get_str_until(proto_str, index, ';', true);
	PbServiceElement* pb_service_element = make_pb_service_element(text, comments);

	// parse single line comment
	PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
	if (single_line_comment != NULL)
	{
		append_list(PbCommentNode, pb_service_element->comments, single_line_comment);
	}
	PbService* obj = (PbService*)(top_stack(object_stack, NULL)->data);
	append_linked_list(pb_service_element, "PbServiceElement", obj->elements);

	g_free(to_void_ptr(&text));
}