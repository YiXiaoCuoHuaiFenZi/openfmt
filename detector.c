/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-07
**    更新日期：    2023-06-01
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
    char *hasBrace = strstr(t, "{");
    g_free(&t);
    return is && hasBrace;
}

bool is_enum(char *line)
{
    char *t = trim(line);
    bool is = starts_with("enum ", t);
    char *hasBrace = strstr(t, "{");
    g_free(&t);
    return is && hasBrace;
}

bool is_service(char *line)
{
    char *t = trim(line);
    bool is = starts_with("service ", t);
    char *hasBrace = strstr(t, "{");
    g_free(&t);
    return is && hasBrace;
}

bool is_extend(char *line)
{
    char *t = trim(line);
    bool is = starts_with("extend ", t);
    char *hasBrace = strstr(t, "{");
    g_free(&t);
    return is && hasBrace;
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
    char *doubleSlash = strstr(line, "//");
    char *slashStar = strstr(line, "/*");
    char *equalSign = strstr(line, "=");
    if (semicolon == NULL)
        return false;

    if (doubleSlash && semicolon > doubleSlash)
        return false;

    if (slashStar && semicolon > slashStar)
        return false;

    if (is_service_element(line))
        return true;

    if (is_map_element(line))
        return true;

    if (equalSign)
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
    int sumCubStr = 0;
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
            sumCubStr++;
        token = strtok(NULL, " ");
    }
    return sumCubStr >= 2;
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
    int sumCubStr = 0;
    while (token != NULL)
    {
        if (strcmp(token, " ") != 0)
            sumCubStr++;
        token = strtok(NULL, " ");
    }
    return sumCubStr == 1;
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
    char *hasBrace = strstr(t, "{");
    g_free(&t);
    return is && hasBrace;
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