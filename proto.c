/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Proto ADT(Abstract Data Type).
**    创建日期：    2022-10-03
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "proto.h"
#include "util/util.h"
#include "lib/str.h"
#include "lib/memory.h"
#include "comment_parser.h"

void print_text(PbText *text)
{
    PrintTextWithColor(text->text, text->color, false);
}

void print_text_list(PbTextList *textList)
{
    PbTextNode *node = textList->next;
    while (node)
    {
        PbText *text = (PbText *) (node->data);
        print_text(text);
        node = node->next;
    }
}

PbText *create_pb_text(char *text, int color)
{
    PbText *pbText = (PbText *) g_malloc(sizeof(PbText));
    pbText->text = text;
    pbText->color = color;
    return pbText;
}

void create_add_pb_text(char *text, int color, PbTextList *textList)
{
    PbText *pbText = create_pb_text(str_copy(text), color);
    append_list(PbTextNode, textList, pbText);
}

void format_protobuf(Protobuf *protobuf, const char *filePath)
{
    PbTextList *textList = create_list(PbTextNode);
    format_syntax(protobuf, textList);
    format_package(protobuf, textList);
    format_options(protobuf, textList);
    format_imports(protobuf, textList);
    format_objects(protobuf, textList);
    format_comments(protobuf, textList);

    if (protobuf->config.preview)
    {
        print_text_list(textList);
    } else
    {
        write_to_file(textList, filePath);
    }

    dispose_list(PbTextNode, textList, free_PbText);
}

char *str_join(PbTextList *textList)
{
    unsigned long int length = 0;
    PbTextNode *node = textList->next;
    while (node)
    {
        PbText *text = (PbText *) (node->data);
        length = length + strlen(text->text);
        node = node->next;
    }
    unsigned long int size = length;
    char *buff = (char *) g_malloc(sizeof(char) * size + 1);

    PbTextNode *cur = textList->next;
    while (cur)
    {
        PbText *text = (PbText *) (cur->data);
        length = length + strlen(text->text);
        strcat(buff, text->text);
        cur = cur->next;
    }
    buff[size] = '\0';
    return buff;
}

void write_to_file(PbTextList *textList, const char *filePath)
{
    FILE *fptr;
    fptr = fopen(filePath, "w");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    PbTextNode *node = textList->next;
    while (node)
    {
        PbText *text = (PbText *) (node->data);
        fprintf(fptr, "%s", text->text);
        node = node->next;
    }

    fclose(fptr);
}

bool has_top_comment(PbCommentList *commentList)
{
    PbCommentNode *cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == TOP)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool has_right_comment(PbCommentList *commentList)
{
    PbCommentNode *cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == RIGHT)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool has_bottom_comment(PbCommentList *commentList)
{
    PbCommentNode *cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == BOTTOM)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void build_top_comment(
        PbCommentList *commentList,
        int color,
        unsigned int indents,
        PbTextList *textList,
        bool includeRightComment
)
{
    if (!has_top_comment(commentList) && !has_right_comment(commentList))
    {
        return;
    }

    PbCommentNode *cur = commentList->next;

    if (has_top_comment(commentList))
    {
        char *spaces = repeat(" ", indents);
        create_add_pb_text(spaces, color, textList); // add indents
        g_free(&spaces);
        create_add_pb_text("/*\n", color, textList);
    } else
    {
        if (has_right_comment(commentList) && includeRightComment)
        {
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, color, textList); // add indents
            g_free(&spaces);
            create_add_pb_text("/*\n", color, textList);
        }
    }

    while (cur)
    {
        if (cur->data->pos == TOP)
        {
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, color, textList); // add indents
            g_free(&spaces);
            if (strcmp(cur->data->text, "") == 0)
            {
                create_add_pb_text("**", color, textList);
            } else
            {
                create_add_pb_text("**    ", color, textList);
                create_add_pb_text(cur->data->text, color, textList);
            }
            create_add_pb_text("\n", color, textList);
        }
        cur = cur->next;
    }

    if (!includeRightComment)
    {
        if (has_top_comment(commentList))
        {
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, color, textList); // add indents
            g_free(&spaces);
            create_add_pb_text("*/\n", color, textList);
            return;
        }
        return;
    }

    cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == RIGHT)
        {
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, color, textList); // add indents
            g_free(&spaces);
            if (strcmp(cur->data->text, "") == 0)
            {
                create_add_pb_text("**", color, textList);
            } else
            {
                create_add_pb_text("**    ", color, textList);
                create_add_pb_text(cur->data->text, color, textList);
            }
            create_add_pb_text(cur->data->text, color, textList);
            create_add_pb_text("\n", color, textList);
        }
        cur = cur->next;
    }
    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, color, textList); // add indents
    g_free(&spaces);
    create_add_pb_text("*/\n", color, textList);
}

void format_right_comment(PbCommentList *commentList, int color, PbTextList *textList)
{
    PbCommentNode *cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == RIGHT)
        {
            create_add_pb_text("// ", color, textList);
            create_add_pb_text(cur->data->text, color, textList);
            return;
        }
        cur = cur->next;
    }
}

void format_bottom_comment(PbCommentList *commentList, int color, unsigned int indents, PbTextList *textList)
{
    if (!has_bottom_comment(commentList))
    {
        return;
    }

    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, color, textList); // add indents
    g_free(&spaces);
    create_add_pb_text("/*\n", color, textList);

    PbCommentNode *cur = commentList->next;
    while (cur)
    {
        if (cur->data->pos == BOTTOM)
        {
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, color, textList); // add indents
            g_free(&spaces);
            if (strcmp(cur->data->text, "") == 0)
            {
                create_add_pb_text("**", color, textList);
            } else
            {
                create_add_pb_text("**    ", color, textList);
                create_add_pb_text(cur->data->text, color, textList);
            }
            create_add_pb_text(cur->data->text, color, textList);
            create_add_pb_text("\n", color, textList);
        }
        cur = cur->next;
    }
    char *spaces_end = repeat(" ", indents);
    create_add_pb_text(spaces_end, color, textList); // add indents
    g_free(&spaces_end);
    create_add_pb_text("*/\n", color, textList);
}

void format_syntax(Protobuf *protobuf, PbTextList *textList)
{
    if (protobuf->syntax == NULL)
    {
        return;
    }
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(protobuf->syntax->comments, colorConfig.comment, 0, textList, config.topComment);
    create_add_pb_text("syntax", colorConfig.syntax_key, textList);
    create_add_pb_text(" = ", colorConfig.default_color, textList);
    create_add_pb_text(protobuf->syntax->value, colorConfig.syntax_value, textList);
    create_add_pb_text(";", colorConfig.default_color, textList);

    if (!config.topComment && has_right_comment(protobuf->syntax->comments))
    {
        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(protobuf->syntax->comments, colorConfig.comment, textList);
    }
    create_add_pb_text("\n\n", colorConfig.default_color, textList);
}

void format_package(Protobuf *protobuf, PbTextList *textList)
{
    if (protobuf->package == NULL)
    {
        return;
    }
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(protobuf->package->comments, colorConfig.comment, 0, textList, config.topComment);
    create_add_pb_text("package", colorConfig.package_key, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(protobuf->package->value, colorConfig.package_value, textList);
    create_add_pb_text(";", colorConfig.default_color, textList);

    if (!config.topComment && has_right_comment(protobuf->package->comments))
    {
        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(protobuf->package->comments, colorConfig.comment, textList);
    }
    create_add_pb_text("\n\n", colorConfig.default_color, textList);
}

void format_option(
        Protobuf *protobuf,
        PbOption *pbOption,
        unsigned int maxOptionNameLength,
        unsigned int maxOptionValueLength,
        PbTextList *textList
)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;
    build_top_comment(pbOption->comments, colorConfig.comment, 0, textList, config.topComment);

    create_add_pb_text("option", colorConfig.option_key, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(pbOption->name, colorConfig.option_name, textList);

    /*
    ** align by equal sign, fill extra spaces between the option name and equal sign.
    */
    if (config.alignByEqualSign)
    {
        unsigned int optionNameLen = strlen(pbOption->name);
        unsigned int fillSpaceAmount = maxOptionNameLength - optionNameLen;
        char *spaces = repeat(" ", fillSpaceAmount);
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
    }
    create_add_pb_text(" = ", colorConfig.default_color, textList);
    create_add_pb_text(pbOption->value, colorConfig.option_value, textList);
    create_add_pb_text(";", colorConfig.default_color, textList);

    if (!config.topComment && has_right_comment(pbOption->comments))
    {
        /*
        ** align comments if align by equal sign, fill extra spaces between the option value and single line comment.
        */
        if (config.alignByEqualSign)
        {
            unsigned int optionValueLen = strlen(pbOption->value);
            unsigned int fillSpaceAmount = maxOptionValueLength - optionValueLen;
            char *spaces = repeat(" ", fillSpaceAmount);
            create_add_pb_text(spaces, colorConfig.default_color, textList);
            g_free(&spaces);
        }

        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(pbOption->comments, colorConfig.comment, textList);
    }
}

unsigned int get_max_option_name_length(Protobuf *protobuf)
{
    PbOptionNode *cur = protobuf->options->next;
    unsigned int maxLength = 0;
    while (cur)
    {
        if (strlen(cur->data->name) > maxLength)
        {
            maxLength = strlen(cur->data->name);
        }
        cur = cur->next;
    }
    return maxLength;
}

unsigned int get_max_option_value_length(Protobuf *protobuf)
{
    PbOptionNode *cur = protobuf->options->next;
    unsigned int maxLength = 0;
    while (cur)
    {
        if (strlen(cur->data->value) > maxLength)
        {
            maxLength = strlen(cur->data->value);
        }
        cur = cur->next;
    }
    return maxLength;
}

void format_options(Protobuf *protobuf, PbTextList *textList)
{
    if (protobuf->options == NULL)
    {
        return;
    }
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;
    unsigned int maxOptionNameLength = get_max_option_name_length(protobuf);
    unsigned int maxOptionValueLength = get_max_option_value_length(protobuf);

    PbOptionNode *cur = protobuf->options->next;
    while (cur)
    {
        format_option(protobuf, cur->data, maxOptionNameLength, maxOptionValueLength, textList);
        create_add_pb_text("\n", colorConfig.default_color, textList);
        cur = cur->next;
    }
    create_add_pb_text("\n", colorConfig.default_color, textList);
}

unsigned int get_max_import_value_length(Protobuf *protobuf)
{
    PbImportNode *cur = protobuf->imports->next;
    unsigned int maxLength = 0;
    while (cur)
    {
        if (strlen(cur->data->value) > maxLength)
        {
            maxLength = strlen(cur->data->value);
        }
        cur = cur->next;
    }
    return maxLength;
}

void format_import(Protobuf *protobuf, PbImport *pbImport, unsigned int maxImportValueLength, PbTextList *textList)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(pbImport->comments, colorConfig.comment, 0, textList, config.topComment);
    create_add_pb_text("import", colorConfig.import_key, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(pbImport->value, colorConfig.import_value, textList);
    create_add_pb_text(";", colorConfig.default_color, textList);

    if (!config.topComment && has_right_comment(pbImport->comments))
    {
        unsigned int importValueLen = strlen(pbImport->value);
        unsigned int fillSpaceAmount = maxImportValueLength - importValueLen;
        char *spaces = repeat(" ", fillSpaceAmount);
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(pbImport->comments, colorConfig.comment, textList);
    }
}

void format_imports(Protobuf *protobuf, PbTextList *textList)
{
    if (protobuf->imports == NULL)
    {
        return;
    }
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;
    unsigned int maxImportValueLength = get_max_import_value_length(protobuf);

    PbImportNode *cur = protobuf->imports->next;
    while (cur)
    {
        format_import(protobuf, cur->data, maxImportValueLength, textList);
        create_add_pb_text("\n", colorConfig.default_color, textList);
        cur = cur->next;
    }
    create_add_pb_text("\n", colorConfig.default_color, textList);
}

void get_max_message_element_length(List elements, MessageElementLengthInfo *messageElementLengthInfo)
{
    List cur = elements->next;
    while (cur)
    {
        if (strcmp(cur->data_type, "PbMessageElement") == 0)
        {
            PbMessageElement *ele = (PbMessageElement *) cur->data;

            unsigned int len1 = strlen(ele->type) + strlen(ele->name);
            if (ele->label)
            {
                len1 = strlen(ele->label) + strlen(ele->type) + strlen(ele->name);
                len1++; // additional space between label and type.
            }
            if (len1 > messageElementLengthInfo->maxLengthBeforeEqualSign)
            {
                messageElementLengthInfo->maxLengthBeforeEqualSign = len1;
            }

            unsigned int len2 = strlen(ele->number);
            if (ele->annotation)
            {
                len2 = strlen(ele->number) + strlen(ele->annotation);
                len2++; // additional space between number and annotation.
            }
            if (len2 > messageElementLengthInfo->maxLengthBetweenEqualSignAndSemicolon)
            {
                messageElementLengthInfo->maxLengthBetweenEqualSignAndSemicolon = len2;
            }
        }
        cur = cur->next;
    }
}

void format_message_element(
        Protobuf *protobuf,
        PbMessageElement *ele,
        unsigned int indents,
        MessageElementLengthInfo meli,
        PbTextList *textList
)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(ele->comments, colorConfig.comment, indents, textList, config.topComment);

    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, colorConfig.default_color, textList); // add indents
    g_free(&spaces);
    unsigned int cmlbes = strlen(ele->type) + strlen(ele->name); // maxLengthBeforeEqualSign of current element.
    if (ele->label)
    {
        cmlbes = strlen(ele->label) + strlen(ele->type) + strlen(ele->name);
        cmlbes++; // additional space between label and type.

        create_add_pb_text(ele->label, colorConfig.message_element_label, textList);
        create_add_pb_text(" ", colorConfig.default_color, textList);
    }
    create_add_pb_text(ele->type, colorConfig.message_element_type, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(ele->name, colorConfig.message_element_name, textList);

    /*
    ** align by equal sign, fill extra spaces between the element name and equal sign.
    */
    if (config.alignByEqualSign)
    {
        unsigned int fillSpaceAmount = meli.maxLengthBeforeEqualSign - cmlbes;
        char *spaces = repeat(" ", fillSpaceAmount);
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
    }

    create_add_pb_text(" = ", colorConfig.default_color, textList);
    create_add_pb_text(ele->number, colorConfig.message_element_number, textList);

    unsigned int cmlbesas = strlen(ele->number); // maxLengthBetweenEqualSignAndSemicolon of current element.
    if (ele->annotation)
    {
        create_add_pb_text(" ", colorConfig.default_color, textList);

        cmlbesas = strlen(ele->number) + strlen(ele->annotation);
        cmlbesas++; // additional space between number and annotation.

        create_add_pb_text(ele->annotation, colorConfig.message_element_annotation, textList);
        create_add_pb_text(";", colorConfig.default_color, textList);
    } else
    {
        create_add_pb_text(";", colorConfig.default_color, textList);
    }

    if (!config.topComment && has_right_comment(ele->comments))
    {
        unsigned int space_amount = meli.maxLengthBetweenEqualSignAndSemicolon - cmlbesas;
        space_amount = space_amount + 2; // make sure there are two spaces between semicolon and single line comment
        char *spaces = repeat(" ", space_amount);
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
        format_right_comment(ele->comments, colorConfig.comment, textList);
    }

    create_add_pb_text("\n", colorConfig.default_color, textList);
}

void format_message_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList)
{
    MessageElementLengthInfo meli = {0, 0};

    get_max_message_element_length(elements, &meli);

    List cur = elements->next;
    while (cur)
    {
        if (strcmp(cur->data_type, "PbMessageElement") == 0)
        {
            PbMessageElement *ele = (PbMessageElement *) cur->data;
            format_message_element(protobuf, ele, indents, meli, textList);
        } else
        {
            format_object(protobuf, cur->data, cur->data_type, indents, textList);
        }
        cur = cur->next;
    }
}


void find_max_enum_element_length(List elements, EnumElementLengthInfo *messageElementLengthInfo)
{
    List cur = elements->next;
    while (cur)
    {
        if (strcmp(cur->data_type, "PbEnumElement") == 0)
        {
            PbEnumElement *ele = (PbEnumElement *) cur->data;

            if (strlen(ele->name) > messageElementLengthInfo->maxLengthOfName)
            {
                messageElementLengthInfo->maxLengthOfName = strlen(ele->name);
            }

            unsigned int len = strlen(ele->number);
            if (ele->annotation)
            {
                len = strlen(ele->number) + strlen(ele->annotation);
                len++; // additional space between number and annotation.
            }
            if (len > messageElementLengthInfo->maxLengthBetweenEqualSignAndSemicolon)
            {
                messageElementLengthInfo->maxLengthBetweenEqualSignAndSemicolon = len;
            }
        }
        cur = cur->next;
    }
}

void format_enum_element(
        Protobuf *protobuf,
        PbEnumElement *ele,
        unsigned int indents,
        EnumElementLengthInfo eeli,
        PbTextList *textList
)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(ele->comments, colorConfig.comment, indents, textList, config.topComment);

    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, colorConfig.default_color, textList); // add indents
    g_free(&spaces);
    create_add_pb_text(ele->name, colorConfig.enum_element_name, textList);

    /*
    ** align by equal sign, fill extra spaces between the element name and equal sign.
    */
    if (config.alignByEqualSign)
    {
        char *spaces = repeat(" ", eeli.maxLengthOfName - strlen(ele->name));
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
    }

    create_add_pb_text(" = ", colorConfig.default_color, textList);
    create_add_pb_text(ele->number, colorConfig.enum_element_number, textList);

    unsigned int cmlbesas = strlen(ele->number); // maxLengthBetweenEqualSignAndSemicolon of current element.
    if (ele->annotation)
    {
        create_add_pb_text(" ", colorConfig.default_color, textList);

        cmlbesas = strlen(ele->number) + strlen(ele->annotation);
        cmlbesas++; // additional space between number and annotation.

        create_add_pb_text(ele->annotation, colorConfig.enum_element_annotation, textList);
        create_add_pb_text(";", colorConfig.default_color, textList);
    } else
    {
        create_add_pb_text(";", colorConfig.default_color, textList);
    }


    if (!config.topComment && has_right_comment(ele->comments))
    {
        unsigned int space_amount = eeli.maxLengthBetweenEqualSignAndSemicolon - cmlbesas;
        space_amount = space_amount + 2; // make sure there are two spaces between semicolon and single line comment
        char *spaces = repeat(" ", space_amount);
        create_add_pb_text(spaces, colorConfig.default_color, textList);
        g_free(&spaces);
        format_right_comment(ele->comments, colorConfig.comment, textList);
    }

    create_add_pb_text("\n", colorConfig.default_color, textList);
}

void format_enum_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList)
{
    EnumElementLengthInfo eeli = {0, 0};

    find_max_enum_element_length(elements, &eeli);

    List cur = elements->next;
    while (cur)
    {
        if (strcmp(cur->data_type, "PbEnumElement") == 0)
        {
            PbEnumElement *ele = (PbEnumElement *) cur->data;
            format_enum_element(protobuf, ele, indents, eeli, textList);
        }
        cur = cur->next;
    }
}

void format_service_element(
        Protobuf *protobuf,
        PbServiceElement *ele,
        unsigned int indents,
        PbTextList *textList
)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(ele->comments, colorConfig.comment, indents, textList, config.topComment);
    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, colorConfig.default_color, textList); // add indents
    g_free(&spaces);
    create_add_pb_text(ele->label, colorConfig.service_element_label, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(ele->name, colorConfig.service_element_name, textList);
    create_add_pb_text(" (", colorConfig.default_color, textList);
    create_add_pb_text(ele->request, colorConfig.service_element_request, textList);
    create_add_pb_text(")", colorConfig.default_color, textList);
    create_add_pb_text(" returns ", colorConfig.service_element_label, textList);
    create_add_pb_text("(", colorConfig.default_color, textList);
    create_add_pb_text(ele->response, colorConfig.service_element_response, textList);
    create_add_pb_text(");", colorConfig.default_color, textList);
    if (!config.topComment && has_right_comment(ele->comments))
    {
        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(ele->comments, colorConfig.comment, textList);
    }
    create_add_pb_text("\n", colorConfig.default_color, textList);
}

void format_service_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList)
{
    List cur = elements->next;
    while (cur)
    {
        if (strcmp(cur->data_type, "PbServiceElement") == 0)
        {
            PbServiceElement *ele = (PbServiceElement *) cur->data;
            format_service_element(protobuf, ele, indents, textList);
        }
        cur = cur->next;
    }
}

void create_object_text(
        char *objectType,
        char *objectName,
        PbCommentList *objectComments,
        List objectElements,
        Protobuf *protobuf,
        unsigned int indents,
        PbTextList *textList,
        void (ElementFormatFunc)(Protobuf *, List, unsigned int, PbTextList *)
)
{
    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    build_top_comment(objectComments, colorConfig.comment, indents, textList, config.topComment);
    char *spaces = repeat(" ", indents);
    create_add_pb_text(spaces, colorConfig.default_color, textList); // add indents
    g_free(&spaces);
    create_add_pb_text(objectType, colorConfig.obj_key, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text(objectName, colorConfig.obj_name, textList);
    create_add_pb_text(" ", colorConfig.default_color, textList);
    create_add_pb_text("{", colorConfig.default_color, textList);

    if (!config.topComment && has_right_comment(objectComments))
    {
        create_add_pb_text("  ", colorConfig.default_color, textList);
        format_right_comment(objectComments, colorConfig.comment, textList);
    }
    create_add_pb_text("\n", colorConfig.default_color, textList);
    ElementFormatFunc(protobuf, objectElements, indents + config.indentsUnit, textList);
    format_bottom_comment(objectComments, colorConfig.comment, indents + config.indentsUnit, textList);
    char *spaces_bottom = repeat(" ", indents);
    create_add_pb_text(spaces_bottom, colorConfig.default_color, textList); // add indents
    g_free(&spaces_bottom);
    create_add_pb_text("}\n", colorConfig.default_color, textList);
}

void format_object(Protobuf *protobuf, void *object, char *data_type, unsigned int indents, PbTextList *textList)
{
    if (strcmp(data_type, "PbMessage") == 0)
    {
        PbMessage *obj = (PbMessage *) object;
        create_object_text(
                "message",
                obj->name,
                obj->comments,
                obj->elements,
                protobuf,
                indents,
                textList,
                format_message_elements
        );
        return;
    }

    if (strcmp(data_type, "PbEnum") == 0)
    {
        PbEnum *obj = (PbEnum *) object;
        create_object_text(
                "enum",
                obj->name,
                obj->comments,
                obj->elements,
                protobuf,
                indents,
                textList,
                format_enum_elements
        );
        return;
    }

    if (strcmp(data_type, "PbService") == 0)
    {
        PbEnum *obj = (PbEnum *) object;
        create_object_text(
                "service",
                obj->name,
                obj->comments,
                obj->elements,
                protobuf,
                indents,
                textList,
                format_service_elements
        );
        return;
    }

    if (strcmp(data_type, "PbOneOf") == 0)
    {
        PbOneOf *obj = (PbOneOf *) object;
        create_object_text(
                "oneof",
                obj->name,
                obj->comments,
                obj->elements,
                protobuf,
                indents,
                textList,
                format_message_elements
        );
        return;
    }

    if (strcmp(data_type, "PbExtend") == 0)
    {
        PbMessage *obj = (PbMessage *) object;
        create_object_text(
                "extend",
                obj->name,
                obj->comments,
                obj->elements,
                protobuf,
                indents,
                textList,
                format_message_elements
        );
        return;
    }
}

void format_objects(Protobuf *protobuf, PbTextList *textList)
{
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;
    List cur = protobuf->objects->next;
    while (cur)
    {
        format_object(protobuf, cur->data, cur->data_type, 0, textList);
        if (cur->next)
        {
            create_add_pb_text("\n", colorConfig.default_color, textList);
        }
        cur = cur->next;
    }
}


void format_comments(Protobuf *protobuf, PbTextList *textList)
{
    if (protobuf->comments == NULL)
        return;

    PbConfig config = protobuf->config;
    PbTextColorConfig colorConfig = protobuf->config.textColorConfig;

    int indents = config.indentsUnit;

    // convert all comments as bottom comments
    PbCommentNode *cur = protobuf->comments->next;
    create_add_pb_text("/*\n", colorConfig.default_color, textList);
    while (cur)
    {
        if (cur->data->pos == BOTTOM)
        {
            create_add_pb_text("**", colorConfig.comment, textList);
            char *spaces = repeat(" ", indents);
            create_add_pb_text(spaces, colorConfig.default_color, textList); // add indents
            g_free(&spaces);
            create_add_pb_text(cur->data->text, colorConfig.comment, textList);
            create_add_pb_text("\n", colorConfig.default_color, textList);
        }
        cur = cur->next;
    }
    create_add_pb_text("*/", colorConfig.comment, textList);
    create_add_pb_text("\n", colorConfig.default_color, textList);
}

void free_comment_list(PbCommentList **comments)
{
    dispose_list(PbCommentList, (*comments), free_PbComment);
}

void free_PbText(PbTextNode *ptr)
{
    PbText *t = (PbText *) (ptr->data);
    g_free(&t->text);
    g_free(&t);
}

void free_pb_message(PbMessage *obj)
{
    g_free(&obj->id);
    g_free(&obj->parentId);
    g_free(&obj->name);
    free_comment_list(&obj->comments);
    free_objects(&obj->elements);
    g_free(&obj);
}

void free_pb_enum(PbEnum *obj)
{
    g_free(&obj->id);
    g_free(&obj->name);
    free_comment_list(&obj->comments);
    free_objects(&obj->elements);
    g_free(&obj);
}

void free_pb_service(PbService *obj)
{
    g_free(&obj->id);
    g_free(&obj->name);
    free_comment_list(&obj->comments);
    free_objects(&obj->elements);
    g_free(&obj);
}

void free_pb_extend(PbExtend *obj)
{
    g_free(&obj->id);
    g_free(&obj->name);
    free_comment_list(&obj->comments);
    free_objects(&obj->elements);
    g_free(&obj);
}

void free_pb_oneof(PbOneOf *obj)
{
    g_free(&obj->id);
    g_free(&obj->name);
    g_free(&obj->parentId);
    free_comment_list(&obj->comments);
    free_objects(&obj->elements);
    g_free(&obj);
}

void free_pb_message_element(PbMessageElement *obj)
{
    g_free(&obj->label);
    g_free(&obj->type);
    g_free(&obj->name);
    g_free(&obj->number);
    g_free(&obj->annotation);
    free_comment_list(&obj->comments);
    g_free(&obj);
}

void free_pb_enum_element(PbEnumElement *obj)
{
    g_free(&obj->name);
    g_free(&obj->number);
    g_free(&obj->annotation);
    free_comment_list(&obj->comments);
    g_free(&obj);
}

void free_pb_service_element(PbServiceElement *obj)
{
    g_free(&obj->label);
    g_free(&obj->name);
    g_free(&obj->request);
    g_free(&obj->response);
    free_comment_list(&obj->comments);
    g_free(&obj);
}

void free_objects(List *object_list)
{

    List head = *object_list;
    List cur = head->next;

    while (cur != NULL)
    {
        PtrToNode temp_node = cur;
        cur = cur->next;

        char *data_type = temp_node->data_type;

        if (strcmp(data_type, "PbMessage") == 0)
        {
            PbMessage *obj = temp_node->data;
            free_pb_message(obj);
        }

        if (strcmp(data_type, "PbEnum") == 0)
        {
            PbEnum *obj = temp_node->data;
            free_pb_enum(obj);
        }

        if (strcmp(data_type, "PbService") == 0)
        {
            PbService *obj = temp_node->data;
            free_pb_service(obj);
        }

        if (strcmp(data_type, "PbExtend") == 0)
        {
            PbExtend *obj = temp_node->data;
            free_pb_extend(obj);
        }

        if (strcmp(data_type, "PbOneOf") == 0)
        {
            PbOneOf *obj = temp_node->data;
            free_pb_oneof(obj);
        }

        if (strcmp(data_type, "PbMessageElement") == 0)
        {
            PbMessageElement *obj = temp_node->data;
            free_pb_message_element(obj);
        }

        if (strcmp(data_type, "PbEnumElement") == 0)
        {
            PbEnumElement *obj = temp_node->data;
            free_pb_enum_element(obj);
        }

        if (strcmp(data_type, "PbServiceElement") == 0)
        {
            PbServiceElement *obj = temp_node->data;
            free_pb_service_element(obj);
        }

        g_free(&temp_node->data_type);
        g_free(&temp_node);
    }
    g_free(&head);
}

void free_protobuf(Protobuf *protobuf)
{
    if (protobuf->syntax != NULL)
    {
        g_free(&protobuf->syntax->value);
        free_comment_list(&protobuf->syntax->comments);
        g_free(&protobuf->syntax);
    }

    if (protobuf->package != NULL)
    {
        g_free(&protobuf->package->value);
        free_comment_list(&protobuf->package->comments);
        g_free(&protobuf->package);
    }

    if (protobuf->options)
    {
        PbOptionNode *head = protobuf->options;
        PbOptionNode *cur = head->next;
        while (cur)
        {
            PbOptionNode *t_node = cur;
            cur = cur->next;
            g_free(&t_node->data->name);
            g_free(&t_node->data->value);
            free_comment_list(&t_node->data->comments);
            g_free(&t_node->data);
            g_free(&t_node);
        }
        g_free(&head);
    }

    if (protobuf->imports != NULL)
    {
        PbImportNode *head = protobuf->imports;
        PbImportNode *cur = head->next;
        while (cur)
        {
            PbImportNode *t_node = cur;
            cur = cur->next;
            g_free(&t_node->data->value);
            free_comment_list(&t_node->data->comments);
            g_free(&t_node->data);
            g_free(&t_node);
        }
        g_free(&head);
    }
    free_objects(&protobuf->objects);
    if (protobuf->comments != NULL)
    {
        free_comment_list(&protobuf->comments);
    }
    g_free(&protobuf);
}