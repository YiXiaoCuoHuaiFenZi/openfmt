/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-07
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include <printf.h>
#include "detector.h"
#include "lib/str.h"
#include "lib/memory.h"

bool is_syntax(char *line)
{
    char *t = trim(line);
    char *r = replace(" ", "", t);
    bool is = starts_with("syntax=", r);
    g_free(&t);
    g_free(&r);
    return is;
}

bool is_package(char *line)
{
    char *t = trim(line);
    bool is = starts_with("package ", t);
    g_free(&t);
    return is;
}

bool is_option(char *line)
{
    char *t = trim(line);
    bool is = starts_with("option ", t);
    g_free(&t);
    return is;
}

bool is_import(char *line)
{
    char *t = trim(line);
    bool is = starts_with("import ", t);
    g_free(&t);
    return is;
}

bool is_message(char *line)
{
    char *t = trim(line);
    bool is = starts_with("message ", t);
    char *has_brace = strstr(t, "{");
    g_free(&t);
    return is && has_brace;
}

bool is_enum(char *line)
{
    char *t = trim(line);
    bool is = starts_with("enum ", t);
    char *has_brace = strstr(t, "{");
    g_free(&t);
    return is && has_brace;
}

bool is_service(char *line)
{
    char *t = trim(line);
    bool is = starts_with("service ", t);
    char *has_brace = strstr(t, "{");
    g_free(&t);
    return is && has_brace;
}

bool is_extend(char *line)
{
    char *t = trim(line);
    bool is = starts_with("extend ", t);
    char *has_brace = strstr(t, "{");
    g_free(&t);
    return is && has_brace;
}

bool is_map_element(char *line)
{
    // the map element looks like: map<string, Project> projects = 3;
    char *t = trim(line);
    char *r = replace(" ", "", t);
    bool is = starts_with("map<", r);
    g_free(&t);
    g_free(&r);
    return is;
}

bool is_element(char *line)
{
    char *semicolon = strstr(line, ";");
    char *double_slash = strstr(line, "//");
    char *slash_star = strstr(line, "/*");
    char *equal_sign = strstr(line, "=");
    if (semicolon == NULL)
        return false;

    if (double_slash && semicolon > double_slash)
        return false;

    if (slash_star && semicolon > slash_star)
        return false;

    if (is_service_element(line))
        return true;

    if (is_map_element(line))
        return true;

    if (equal_sign)
        return true;

    return false;
}

bool is_message_element(char *line)
{
    // Example: repeated common.Tiger work_legs = 3;               // Chronological work  legs
    if (!is_element(line))
        return false;

    if (is_syntax(line))
        return false;

    if (is_service_element(line))
        return false;

    if (is_map_element(line))
        return true;

    // copy original string (char *) to char [], so it can use strtok to detect substrings(split).
    unsigned int len = strlen(line);
    char str[len];
    for (int index = 0; index < len; index++)
    {
        str[index] = line[index];
    }

    char *token = strtok(str, "=");
    if (token == NULL)
    {
        return false; // no equal sign, return false.
    }
    token = strtok(token, " ");

    // check if the left of equal sign has only one string(the enum element name).
    int space_amount = 0;
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
            space_amount++;
        token = strtok(NULL, " ");
    }
    return space_amount >= 2;
}

bool is_enum_element(char *line)
{
    if (!is_element(line))
        return false;

    // copy original string (char *) to char [], so it can use strtok to detect substrings(split).
    unsigned int len = strlen(line);
    char str[len];
    for (int index = 0; index < len; index++)
    {
        str[index] = line[index];
    }

    char *token = strtok(str, "=");
    if (token == NULL)
    {
        return false; // no equal sign, return false.
    }
    token = strtok(token, " ");

    // check if the left of equal sign has only one string(the enum element name).
    int space_amount = 0;
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
            space_amount++;
        token = strtok(NULL, " ");
    }
    return space_amount == 1;
}

bool is_service_element(char *line)
{
    char *t = trim(line);
    bool is = starts_with("rpc ", t);
    g_free(&t);
    return is;
}

bool is_extend_element(char *line)
{
    return NULL;
}

bool is_oneof(char *line)
{
    char *t = trim(line);
    bool is = starts_with("oneof ", t);
    char *has_brace = strstr(t, "{");
    g_free(&t);
    return is && has_brace;
}

PbType get_pb_type(char *line)
{
    if (is_syntax(line))
        return Syntax;
    if (is_package(line))
        return Package;
    if (is_option(line))
        return Option;
    if (is_import(line))
        return Import;
    if (is_message(line))
        return Message;
    if (is_enum(line))
        return Enum;
    if (is_service(line))
        return Service;
    if (is_extend(line))
        return Extend;
    if (is_message_element(line))
        return MessageElement;
    if (is_extend_element(line))
        return ExtendElement;
    if (is_enum_element(line))
        return EnumElement;
    if (is_service_element(line))
        return ServiceElement;
    if (is_oneof(line))
        return OneOf;
    return Unknown;
}