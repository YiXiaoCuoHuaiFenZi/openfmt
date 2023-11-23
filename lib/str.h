/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    generic method of string implementations.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
#ifndef OPENFMT_STR_H
#define OPENFMT_STR_H

#include <stdbool.h>
#include "type.h"

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    copy a string.
**    参数列表：    str:    original string to be copied.
**                return: new copy of the str.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* str_copy(const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    trim space at the front and end of a string, return a copy.
**    参数列表：    str:    original string.
**                return: trimmed string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* trim(const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    trim a string by removing prefix.
**    参数列表：    str:    original string.
**                prefix: prefix substring to be trimmed.
**                return: trimmed string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* trim_prefix(const char* str, const char* prefix);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    trim a string by removing suffix.
**    参数列表：    str:    original string.
**                suffix: suffix substring to be trimmed.
**                return: trimmed string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* trim_suffix(const char* str, const char* suffix);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    trim a string by removing started substring and ended substring.
**    参数列表：    str:    original string.
**                substr: substring to be trimmed.
**                return: trimmed string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* trim_pre_suf(const char* str, const char* substr);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    check if a string starts with a given substring.
**    参数列表：    pre:    prefix substring.
**                str:    original string.
**                return: true: str starts with pre, false: str does not start with pre.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
bool starts_with(const char* pre, const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    check if a string ends with a given substring.
**    参数列表：    suffix: suffix substring.
**                str:    original string.
**                return: true: str ends with suffix, false: str does not end with suffix
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
bool ends_with(const char* suffix, const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    replace all occurrence of substring with given substring.
**    参数列表：    old:    to be replaced substring.
**                new:    substring to replace the old ones.
**                str:    original string.
**                return: replaced string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* replace(const char* old, const char* new, const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    find the substring between two substrings in original string. return NULL if no any one of substrings
**                exists.
**    参数列表：    str:    whole string to get sub string from.
**                start:  start substring at the front of the target substring.
**                end:    following substring of the target substring.
**                return: target string or NULL.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* sub_str_between_str(const char* str, const char* start, const char* end);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get the binary str of a char. example: return "01100001" if pass 'a' in.
**    参数列表：    ch:     char value want to convert.
**                return: the binary string converted from ch.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* char_to_binary_str(char ch);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get the binary str of an int number.
**                example:
**                    assume the size of int is 4 bytes
**                    return "00000000000000011110001001000000" if pass 123456 in.
**    参数列表：    value:  int value want to convert.
**                return: the binary string converted from value.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* int_to_binary_str(int value);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get the binary str of a string, the binary string of each char is separated by a space.
**                return "00110001 00110010 00110011 00110100 00110101 00110110" if pass "123456" in.
**    参数列表：    str:    string want to convert.
**                return: the binary string converted from str.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* char_to_binary_str_with_space(const char* str);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    convert a string to hex string. return "313233343536" if pass "123456" in.
**    参数列表：    input:  string want to convert.
**                output: string buffer to save the converted hex value.
**                return: void
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
void str_to_hex_str(const char* input, char* output);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    convert byte(unsigned char) array to hex string.
**    参数列表：    input:  byte(unsigned char) array want to convert.
**                len: the size of input array.
**                return: hex string, must be freed by calling free function after using.
**    创建日期：    2023-05-31
**    更新日期：    2023-05-31
***********************************************************************************************************************/
char* bytes_to_hex_str(const byte input[], int len);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    create a new string by repeat specified times.
**                example: input "abc" and 5, it will return "abcabcabcabcabc"
**    参数列表：    s:      string want to repeat.
**                times:  how many times the string to be repeated.
**                return: repeated string.
**    创建日期：    2022-10-05
**    更新日期：    2022-11-09
***********************************************************************************************************************/
char* repeat(const char* s, unsigned int times);

#endif //OPENFMT_STR_H
