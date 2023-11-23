/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse service element.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "lib/str.h"
#include "comment_parser.h"
#include "service_ele_parser.h"
#include "lib/memory.h"

PbServiceElement *parse_pb_service_element(char *line, PbCommentList *top_comments, SQueue line_queue)
{
    //  to avoid impact the original line string, create a copy.
    char *s0 = str_copy(line);
    char *s1 = sub_str_between_str(s0, "rpc ", ";");
    char *s2 = replace("(", "", s1);
    char *s3 = replace(")", "", s2);
    g_free(&s0);
    g_free(&s1);
    g_free(&s2);

    char *parts[4] = {NULL};
    int index = 0;
    char *token = strtok(s3, " ");
    while (token != NULL)
    {
        parts[index] = str_copy(token);
        index++;
        token = strtok(NULL, " ");
    }
    g_free(&s3);

    PbServiceElement *ele = (PbServiceElement *) g_malloc(sizeof(PbServiceElement));

    ele->label = g_malloc(4);   /* why not use ele->label = "rpc"; because String literals are stored in such a  */
    strcpy(ele->label, "rpc");       /* way that they're available for the lifetime of the program.                   */
    ele->label[3] = '\0';
    ele->name = parts[0];
    ele->request = parts[1];
    ele->response = parts[3];
    ele->comments = top_comments;
    g_free(&(parts[2])); // release resource of string "returns"

    PbComment *pb_comment = parse_comment(line);
    if (pb_comment != NULL)
    {
        append_list(PbCommentNode, ele->comments, pb_comment);
    }
    de_str_queue(line_queue);

    return ele;
}

PbServiceElement *new_parse_pb_service_element(char *text, PbCommentList *top_comments)
{
	//  to avoid impact the original line string, create a copy.
	char *s0 = str_copy(text);
	char *s1 = sub_str_between_str(s0, "rpc ", ";");
	char *s2 = replace("(", "", s1);
	char *s3 = replace(")", "", s2);
	g_free(&s0);
	g_free(&s1);
	g_free(&s2);

	char *parts[4] = {NULL};
	int index = 0;
	char *token = strtok(s3, " ");
	while (token != NULL)
	{
		parts[index] = str_copy(token);
		index++;
		token = strtok(NULL, " ");
	}
	g_free(&s3);

	PbServiceElement *ele = (PbServiceElement *) g_malloc(sizeof(PbServiceElement));

	ele->label = g_malloc(4);   /* why not use ele->label = "rpc"; because String literals are stored in such a  */
	strcpy(ele->label, "rpc");       /* way that they're available for the lifetime of the program.                   */
	ele->label[3] = '\0';
	ele->name = parts[0];
	ele->request = parts[1];
	ele->response = parts[3];
	ele->comments = top_comments;
	g_free(&(parts[2])); // release resource of string "returns"

	return ele;
}