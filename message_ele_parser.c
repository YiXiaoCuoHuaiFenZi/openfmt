/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message element.
**    创建日期：    2022-11-11
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "message_ele_parser.h"
#include "comment_parser.h"
#include "lib/str.h"
#include "lib/memory.h"

PbMessageElement *parse_pb_message_element(char *line, PbCommentList *topComments, SQueue lineQueue)
{
    PbMessageElement *pbMessageElement = NULL;
    char *s0 = strstr(line, "map<");
    if (s0)
    {
        pbMessageElement = create_map_message_element(line, topComments);
    } else
    {
        pbMessageElement = create_common_message_element(line, topComments);
    }
    DeSQueue(lineQueue);

    return pbMessageElement;
}

PbMessageElement *create_message_element(
        char *label,
        char *type,
        char *name,
        char *number,
        char *annotation,
        PbCommentList *comments
)
{
    PbMessageElement *pbMessageElement = (PbMessageElement *) g_malloc(sizeof(PbMessageElement));
    pbMessageElement->label = label;
    pbMessageElement->type = type;
    pbMessageElement->name = name;
    pbMessageElement->number = number;
    pbMessageElement->annotation = annotation;
    pbMessageElement->comments = comments;

    return pbMessageElement;
}

PbMessageElement *create_map_message_element(char *line, PbCommentList *topComments)
{
    //  map<string,       Project> projects = 3; // map field comment d
    char *s1 = sub_str_between_str(line, "<", ",");
    char *map_type = trim(s1);

    char *s2 = sub_str_between_str(line, ",", ">");
    char *map_value = trim(s2);

    char *s3 = sub_str_between_str(line, ">", "=");
    char *name = trim(s3);

    char *s4 = sub_str_between_str(line, "=", ";");
    char *number = trim(s4);

    unsigned int size = strlen("map<") + strlen(map_type) + strlen(", ") + strlen(map_value) + strlen(">") + 1;
    char *type = g_malloc(size);
    strcat(type, "map<");
    strcat(type, map_type);
    strcat(type, ", ");
    strcat(type, map_value);
    strcat(type, ">");
    type[size - 1] = '\0';

    PbComment *pbComment = parse_comment(line);
    if (pbComment != NULL)
    {
        append_list(PbCommentNode, topComments, pbComment);
    }

    PbMessageElement *PbMessageElement = create_message_element(NULL, type, name, number, NULL, topComments);

    g_free(&s1);
    g_free(&map_type);
    g_free(&s2);
    g_free(&map_value);
    g_free(&s3);
    g_free(&s4);

    return PbMessageElement;
}

PbMessageElement *create_common_message_element(char *line, PbCommentList *topComments)
{
    // common.RequestContext  request_context = 1;            // Basic request context data
    //  char *s1 = strtok(line, ";");
    //  to avoid impact the original line string, create a copy.
    char *line_copy = str_copy(line);
    char *s2 = strtok(line_copy, "=");

    char *parts[5] = {NULL};
    int index = 0;
    char *token = strtok(s2, " ");
    while (token != NULL)
    {
        parts[index] = str_copy(token);
        index++;
        token = strtok(NULL, " ");
    }
    g_free(&line_copy);

    int validValueCount = 0;
    for (int i = 0; i < 5; i++)
    {
        if (parts[i])
        {
            validValueCount++;
        }
    }

    char *label = NULL;
    char *type = NULL;
    char *name = NULL;
    char *number = NULL;
    char *annotation = NULL;
    if (validValueCount == 2)
    {
        type = parts[0];
        name = parts[1];
    }

    if (validValueCount == 3)
    {
        label = parts[0];
        type = parts[1];
        name = parts[2];
    }

    char *s3 = sub_str_between_str(line, "=", ";");
    number = trim(s3);
    g_free(&s3);

    // string market = 1 [(validate.rules).string.len = 2]; // The traveller
    char *hasLeftSquareBracket = strstr(line, "[");
    char *hasRightSquareBracket = strstr(line, "]");
    if (hasLeftSquareBracket && hasRightSquareBracket)
    {
        // get the number value.
        char *s4 = sub_str_between_str(line, "=", "[");
        g_free(&number);
        number = trim(s4);
        g_free(&s4);

        // get the annotation value.
        char *s5 = sub_str_between_str(line, "[", ";");  //  the annotation maybe contains ']' so not get the value by "[" and "]"
        char *s6 = trim(s5);
        unsigned int size = strlen(s6) + 2; // '[', and '\0'
        annotation = (char *) g_malloc(size);
        strcat(annotation, "[");
        strcat(annotation, s6);
        // strcat(annotation, "]");
        annotation[size - 1] = '\0';
        g_free(&s5);
        g_free(&s6);
    }

    PbComment *pbComment = parse_comment(line);
    if (pbComment != NULL)
    {
        append_list(PbCommentNode, topComments, pbComment);
    }

    PbMessageElement *pbMessageElement = create_message_element(label, type, name, number, annotation, topComments);

    return pbMessageElement;
}

