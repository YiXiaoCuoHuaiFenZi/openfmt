/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Provide methods to deserialize proto file to Protobuf object.
**    创建日期：    2022-09-30
**    更新日期：    2023-03-17
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

Protobuf *parse(const char *filePath)
{
    Protobuf *protobuf = (Protobuf *) g_malloc(sizeof(Protobuf));
    protobuf->syntax = NULL;
    protobuf->package = NULL;
    protobuf->options = NULL;
    protobuf->imports = NULL;
    protobuf->objects = CreateList();
    protobuf->colorfulTextList = NULL;
    PbTextColorConfig textColorConfig;
    textColorConfig.default_color = 0;
    textColorConfig.default_key_word = 93;
    textColorConfig.syntax_key = 93;
    textColorConfig.syntax_value = 92;
    textColorConfig.package_key = 93;
    textColorConfig.package_value = 92;
    textColorConfig.option_key = 93;
    textColorConfig.option_name = 97;
    textColorConfig.option_value = 92;
    textColorConfig.import_key = 93;
    textColorConfig.import_value = 92;
    textColorConfig.obj_key = 93;
    textColorConfig.obj_name = 97;
    textColorConfig.message_element_key = 196;
    textColorConfig.message_element_label = 93;
    textColorConfig.message_element_type = 32;
    textColorConfig.message_element_name = 95;
    textColorConfig.message_element_number = 94;
    textColorConfig.message_element_annotation = 97;
    textColorConfig.enum_element_name = 95;
    textColorConfig.enum_element_number = 94;
    textColorConfig.enum_element_annotation = 97;
    textColorConfig.service_element_label = 93;
    textColorConfig.service_element_name = 95;
    textColorConfig.service_element_request = 97;
    textColorConfig.service_element_response = 97;
    textColorConfig.comment = 90;

    PbConfig config;
    config.indentsUnit = 4;
    config.alignByEqualSign = true;
    config.topComment = false;
    config.commentMaxLength = 10000;
    config.preview = false;
    config.textColorConfig = textColorConfig;

    protobuf->config = config;
    protobuf->comments = NULL;

    SQueue lines = ReadLineToSQueue(filePath);
    parse_string_queue(protobuf, lines);
    DisposeSQueue(lines);
    return protobuf;
}

void parse_string_queue(Protobuf *protobuf, SQueue lineQueue)
{
    if (IsEmptySQueue(lineQueue))
        return;

    PbCommentList *topComments = make_top_comments(lineQueue);

    if (IsEmptySQueue(lineQueue))
    {
        if (topComments->next != NULL)
        {
            // convert all comments as bottom comments
            PbCommentNode *cur = topComments->next;
            while (cur)
            {
                cur->data->pos = BOTTOM;
                cur = cur->next;
            }
            protobuf->comments = topComments;
        } else
        {
            dispose_list(PbCommentNode, topComments, free_PbComment);
        }
        return;
    }

    char *line = lineQueue->head->str;
    PbType pbType = get_pb_type(line);
    switch (pbType)
    {
        case Syntax:
        {
            PbSyntax *syntax = parse_syntax(line);
            syntax->comments = topComments;
            protobuf->syntax = syntax;
            PbComment *pbComment = parse_comment(line);
            if (pbComment != NULL)
            {
                append_list(PbCommentNode, syntax->comments, pbComment);
            }
            DeSQueue(lineQueue);
            break;
        }
        case Package:
        {
            PbPackage *pbPackage = parse_package(line);
            pbPackage->comments = topComments;
            protobuf->package = pbPackage;
            PbComment *pbComment = parse_comment(line);
            if (pbComment != NULL)
            {
                append_list(PbCommentNode, pbPackage->comments, pbComment);
            }
            DeSQueue(lineQueue);
            break;
        }
        case Option:
        {
            PbOption *pbOption = parse_option(line);
            pbOption->comments = topComments;
            if (protobuf->options == NULL)
            {
                protobuf->options = create_list(PbOptionNode);
            }
            append_list(PbOptionNode, protobuf->options, pbOption);
            PbComment *pbComment = parse_comment(line);
            if (pbComment != NULL)
            {
                append_list(PbCommentNode, pbOption->comments, pbComment);
            }
            DeSQueue(lineQueue);
            break;
        }
        case Import:
        {
            PbImport *pbImport = parse_import(line);
            pbImport->comments = topComments;
            if (protobuf->imports == NULL)
            {
                protobuf->imports = create_list(PbImportNode);
            }
            append_list(PbImportNode, protobuf->imports, pbImport);
            PbComment *pbComment = parse_comment(line);
            if (pbComment != NULL)
            {
                append_list(PbCommentNode, pbImport->comments, pbComment);
            }
            DeSQueue(lineQueue);
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
            state->obj_dic = CreateGHashTable(G_CAPACITY);

            parse_object(protobuf, lineQueue, topComments, state);
            // TODO release resource of state, and state->obj_dic
            FreeGHashTable(state->obj_dic);
            g_free(&state);//"        "
            int d = 0;
        }
    }
    parse_string_queue(protobuf, lineQueue);
}

