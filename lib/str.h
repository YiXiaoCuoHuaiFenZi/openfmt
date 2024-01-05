/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   generic method of string implementations.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
#ifndef OPENFMT_STR_H
#define OPENFMT_STR_H

#include <stdbool.h>
#include "type.h"

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   copy a string.
**    Parameters:      str:    original string to be copied.
**                     return: new copy of the str.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* str_copy(const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   trim space at the front and end of a string, return a copy.
**    Parameters:      str:    original string.
**                     return: trimmed string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* trim(const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   trim a string by removing prefix.
**    Parameters:      str:    original string.
**                     prefix: prefix substring to be trimmed.
**                     return: trimmed string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* trim_prefix(const char* str, const char* prefix);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   trim a string by removing suffix.
**    Parameters:      str:    original string.
**                     suffix: suffix substring to be trimmed.
**                     return: trimmed string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* trim_suffix(const char* str, const char* suffix);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   trim a string by removing started substring and ended substring.
**    Parameters:      str:    original string.
**                     substr: substring to be trimmed.
**                     return: trimmed string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* trim_pre_suf(const char* str, const char* substr);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   check if a string starts with a given substring.
**    Parameters:      pre:    prefix substring.
**                     str:    original string.
**                     return: true: str starts with pre, false: str does not start with pre.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
bool starts_with(const char* pre, const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   check if a string ends with a given substring.
**    Parameters:      suffix: suffix substring.
**                     str:    original string.
**                     return: true: str ends with suffix, false: str does not end with suffix
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
bool ends_with(const char* suffix, const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   replace all occurrence of substring with given substring.
**    Parameters:      old:    to be replaced substring.
**                     new:    substring to replace the old ones.
**                     str:    original string.
**                     return: replaced string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* replace(const char* old, const char* new, const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   find the substring between two substrings in original string. return NULL if no any one of
**                     substrings exists.
**    Parameters:      str:    whole string to get sub string from.
**                     start:  start substring at the front of the target substring.
**                     end:    following substring of the target substring.
**                     return: target string or NULL.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* sub_str_between_str(const char* str, const char* start, const char* end);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get the binary str of a char. example: return "01100001" if pass 'a' in.
**    Parameters:      ch:     char value want to convert.
**                     return: the binary string converted from ch.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* char_to_binary_str(char ch);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get the binary str of an int number.
**                     example:
**                       assume the size of int is 4 bytes
**                     return "00000000000000011110001001000000" if pass 123456 in.
**    Parameters:      value:  int value want to convert.
**                     return: the binary string converted from value.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* int_to_binary_str(int value);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get the binary str of a string, the binary string of each char is separated by a space.
**                     return "00110001 00110010 00110011 00110100 00110101 00110110" if pass "123456" in.
**    Parameters:      str:    string want to convert.
**                     return: the binary string converted from str.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* char_to_binary_str_with_space(const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   convert a string to hex string. return "313233343536" if pass "123456" in.
**    Parameters:      input:  string want to convert.
**                     output: string buffer to save the converted hex value.
**                     return: void
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
void str_to_hex_str(const char* input, char* output);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   convert byte(unsigned char) array to hex string.
**    Parameters:      input:  byte(unsigned char) array want to convert.
**                     len: the size of input array.
**                     return: hex string, must be freed by calling free function after using.
**    Created Date:    2023-05-31
**    Updated Date:    2023-05-31
***********************************************************************************************************************/
char* bytes_to_hex_str(const byte input[], int len);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   create a new string by repeat specified times.
**                     example: input "abc" and 5, it will return "abcabcabcabcabc"
**    Parameters:      s:      string want to repeat.
**                     times:  how many times the string to be repeated.
**                     return: repeated string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* repeat(const char* s, unsigned int times);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   pick up a sub-string from the string start from the first charactor to the target charactor.
**                     example one: input "abcdefghigklm", 'e', and false, it will return "abcd"
**                     example two: input "abcdefghigklm", 'e', and true, it will return "abcde"
**    Parameters:      s:       string look substring from.
**                     ch:      target charactor looks for.
**                     include: if the sub-string include the target chractor.
**                     return: sub-string meets the condition or NULL when no target chractor exits in the string.
**    Created Date:    2023-12-08
**    Updated Date:    2023-12-08
***********************************************************************************************************************/
char* pick_str_until(const char* s, char ch, bool include);

#endif //OPENFMT_STR_H
