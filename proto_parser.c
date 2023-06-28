/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Provide methods to deserialize proto file to Protobuf object.
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "proto_parser.h"
#include "util/file_helper.h"
#include "comment_parser.h"
#include "detector.h"
#include "syntax_parser.h"
#include "package_parser.h"
#include "option_parser.h"
#include "lib/str_queue.h"
#include "import_parser.h"
#include "object_parser.h"
#include "lib/memory.h"

Protobuf *parse(const char *file_path)
{
    Protobuf *protobuf = (Protobuf *) g_malloc(sizeof(Protobuf));
    protobuf->syntax = NULL;
    protobuf->package = NULL;
    protobuf->options = NULL;
    protobuf->imports = NULL;
    protobuf->objects = create_linked_list();
    protobuf->colorful_text_list = NULL;
    PbTextColorConfig text_color_config;
    text_color_config.default_color = 0;
    text_color_config.default_key_word = 93;
    text_color_config.syntax_key = 93;
    text_color_config.syntax_value = 92;
    text_color_config.package_key = 93;
    text_color_config.package_value = 92;
    text_color_config.option_key = 93;
    text_color_config.option_name = 97;
    text_color_config.option_value = 92;
    text_color_config.import_key = 93;
    text_color_config.import_value = 92;
    text_color_config.obj_key = 93;
    text_color_config.obj_name = 97;
    text_color_config.message_element_key = 196;
    text_color_config.message_element_label = 93;
    text_color_config.message_element_type = 32;
    text_color_config.message_element_name = 95;
    text_color_config.message_element_number = 94;
    text_color_config.message_element_annotation = 97;
    text_color_config.enum_element_name = 95;
    text_color_config.enum_element_number = 94;
    text_color_config.enum_element_annotation = 97;
    text_color_config.service_element_label = 93;
    text_color_config.service_element_name = 95;
    text_color_config.service_element_request = 97;
    text_color_config.service_element_response = 97;
    text_color_config.comment = 90;

    PbConfig config;
    config.indents_unit = 4;
    config.align_by_equal_sign = true;
    config.top_comment = false;
    config.max_comment_len = 10000;
    config.preview = false;
    config.text_color_config = text_color_config;

    protobuf->config = config;
    protobuf->comments = NULL;

    SQueue lines = read_line_to_str_queue(file_path);
    parse_string_queue(protobuf, lines);
    dispose_str_queue(lines);
    return protobuf;
}

void parse_string_queue(Protobuf *protobuf, SQueue line_queue)
{
    if (is_empty_str_queue(line_queue))
        return;

    PbCommentList *top_comments = make_top_comments(line_queue);

    if (is_empty_str_queue(line_queue))
    {
        if (top_comments->next != NULL)
        {
            // convert all comments as bottom comments
            PbCommentNode *cur = top_comments->next;
            while (cur)
            {
                cur->data->pos = BOTTOM;
                cur = cur->next;
            }
            protobuf->comments = top_comments;
        } else
        {
            dispose_list(PbCommentNode, top_comments, free_PbComment);
        }
        return;
    }

    char *line = line_queue->head->str;
    PbType pb_type = get_pb_type(line);
    switch (pb_type)
    {
        case Syntax:
        {
            PbSyntax *syntax = parse_syntax(line);
            syntax->comments = top_comments;
            protobuf->syntax = syntax;
            PbComment *pb_comment = parse_comment(line);
            if (pb_comment != NULL)
            {
                append_list(PbCommentNode, syntax->comments, pb_comment);
            }
            de_str_queue(line_queue);
            break;
        }
        case Package:
        {
            PbPackage *pb_package = parse_package(line);
            pb_package->comments = top_comments;
            protobuf->package = pb_package;
            PbComment *pb_comment = parse_comment(line);
            if (pb_comment != NULL)
            {
                append_list(PbCommentNode, pb_package->comments, pb_comment);
            }
            de_str_queue(line_queue);
            break;
        }
        case Option:
        {
            PbOption *pb_option = parse_option(line);
            pb_option->comments = top_comments;
            if (protobuf->options == NULL)
            {
                protobuf->options = create_list(PbOptionNode);
            }
            append_list(PbOptionNode, protobuf->options, pb_option);
            PbComment *pb_comment = parse_comment(line);
            if (pb_comment != NULL)
            {
                append_list(PbCommentNode, pb_option->comments, pb_comment);
            }
            de_str_queue(line_queue);
            break;
        }
        case Import:
        {
            PbImport *pb_import = parse_import(line);
            pb_import->comments = top_comments;
            if (protobuf->imports == NULL)
            {
                protobuf->imports = create_list(PbImportNode);
            }
            append_list(PbImportNode, protobuf->imports, pb_import);
            PbComment *pb_comment = parse_comment(line);
            if (pb_comment != NULL)
            {
                append_list(PbCommentNode, pb_import->comments, pb_comment);
            }
            de_str_queue(line_queue);
            break;
        }
        default:
        {
            State *state = NULL; // used to store current object
            state = (State *) g_malloc(sizeof(State));
            state->l_brace = 0;
            state->r_brace = 0;
            state->current_obj = NULL;
            state->current_obj_type = NULL;
            state->parent_obj = NULL;
            state->parent_obj_type = NULL;
            state->obj_dic = g_create_hashtable(G_CAPACITY);

            parse_object(protobuf, line_queue, top_comments, state);
            g_free_hashtable(state->obj_dic);
            g_free(&state);
        }
    }
    parse_string_queue(protobuf, line_queue);
}

