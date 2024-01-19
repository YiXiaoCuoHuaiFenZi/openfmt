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


/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return a copy of the string with its first character capitalized and the rest lowercased.
**    Parameters:      s:       original string used to build the new capitalized string, not be changed after call.
**                     return:  new string which only the first character is capitalized.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* capitalize(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return a casefolded copy of the string.
**                     Casefolding is similar to lowercasing but more aggressive because it is intended to remove all
**                     case distinctions in a string. For example, the German lowercase letter 'ß' is equivalent to
**                     "ss". Since it is already lowercase, lower() would do nothing to 'ß'; casefold() converts it
**                     to "ss".
**    Parameters:      s:       original string used to build the new casefolded string, not be changed after call.
**                     return:  new string with all characters are casefolded.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* casefold(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return centered in a string of length width. Padding is done using the specified fillchar. The
**                     copy of original string is returned if width is less than or equal to strlen(s).
**    Parameters:      s:       original string will be placed in the center in width.
**                     c:       fillchar used to padding.
**                     width:   length width.
**                     return:  new string centered in a string of length width.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* center(const char* s, char c, unsigned width);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return the number of non-overlapping occurrences of substring sub in the full string.
**    Parameters:      s:       whole string.
**                     sub:     substring.
**                     return:  occurrences of the sub in s.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
unsigned count(const char* s, char sub);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return the string encoded to bytes.
**    Parameters:      s:        original string to be encoded.
**                     encoding: encoding type.
**                     return:   new string encoded with encoding type.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* encode(const char* s, const char* encoding);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return True if the string ends with the specified suffix, otherwise return False.
**    Parameters:      suffix: suffix substring.
**                     str:    original string.
**                     return: true: str ends with suffix, false: str does not end with suffix
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool endswith(const char* suffix, const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return a copy of the string where all tab characters are replaced by one or more spaces,
**                     depending on the current column and the given tab size.
**    Parameters:      s:       string to be converted.
**                     tabsize: table size.
**                     return:  a copy of the string where all tab characters are replaced by one or more spaces.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* expandtabs(const char* s, unsigned tabsize);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Return the lowest index in the string where substring sub is found within the string s.
**    Parameters:      s:       string to be converted.
**                     sub:     substring to look for.
**                     return:  the lowest index of sub in s.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* find(const char* s, char sub);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Perform a string formatting operation. The string on which this method is called can contain
**                     literal text or replacement fields delimited by braces {}. Each replacement field contains either
**                     the numeric index of a positional argument, or the name of a keyword argument. Returns a copy of
**                     the string where each replacement field is replaced with the string value of the corresponding
**                     argument.
**    Parameters:      s:       template string used to format all arguments.
**                     ...:     variable parameters to fill in the template.
**                     return:  a new string where each replacement field is replaced with the string value of the
**                     corresponding argument.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* format(const char* s, const char* string, ...);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Format a mapping data.
**                     TODO: this method may not be implemented in C.
**    Parameters:      s:       template string used to format mapping data.
**                     mapping: mapping data.
**                     return: Return a formatted version of s, using substitutions from mapping.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* format_map(const char* s, const void* mapping);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Searches the string for a specified value and returns the position of where it was found.
**    Parameters:      s:       full string to look for sub.
**                     sub:     target substring in s.
**                     return: the first occurs potion of the sub in s.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
unsigned int s_index(const char* s, const void* sub);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are alphanumeric.
**    Parameters:      s:      string to be checked
**                     return: True: all characters in the string are alphanumeric, False: at least one character is not
**                     alphanumeric.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isalnum(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     	Returns True if all characters in the string are in the alphabet.
**    Parameters:      s:      string to be checked
**                     return: True: all characters in the string in the alphabet, False: at least one character is not
**                     in the alphabet.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isalpha(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are ascii characters.
**    Parameters:      s:      string to be checked
**                     return: True: all characters in the string are ascii characters, False: at least one character is
**                     not ascii character.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isascii(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are decimals.
**    Parameters:      s:      string to be checked
**                     return: True: all characters in the string are decimals, False: at least one character is not
**                     decimal.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isdecimal(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are digits.
**    Parameters:      s:      string to be checked
**                     return: True: all characters in the string are digits, False: at least one character is not
**                     digit.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isdigit(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if the string is an identifier. A string is considered a valid identifier if it only
**                     contains alphanumeric letters (a-z) and (0-9), or underscores (_). A valid identifier cannot
**                     start with a number, or contain any spaces.
**    Parameters:      s:      string to be checked
**                     return: True: the string is an identifier, False: the string is not an identifier.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isidentifier(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are lower case.
**    Parameters:      s:       string to be checked
**                     return:  True: all characters in the string are lower case, False: at least one character is not
**                     lower case.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_islower(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are numeric.
**    Parameters:      s:       string to be checked
**                     return:  True: all characters in the string are numeric, False: at least one character is not
**                     numeric.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isnumeric(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are printable.
**    Parameters:      s:       string to be checked
**                     return:  True: all characters in the string are printable, False: at least one character is not
**                     printable.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isprintable(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are whitespaces.
**    Parameters:      s:       string to be checked
**                     return:  True: all characters in the string are whitespaces, False: at least one character is not
**                     whitespace.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isspace(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all words in a text start with a upper case letter, AND the rest of the word are
**                     lower case letters, otherwise False.
**    Parameters:      s:       string to be checked
**                     return:  True if all words in a text start with a upper case letter, AND the rest of the word are
**                              lower case letters, otherwise False.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_istitle(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns True if all characters in the string are upper case.
**    Parameters:      s:       string to be checked
**                     return:  True if all characters in the string are upper case.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_isupper(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Converts the elements of an iterable into a string.
**                     TODO: this method may not be implemented in C.
**    Parameters:      con: connector to connect elements of data items.
**                     data:    iterable data.
**                     return:  elements string connected with con.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_join(const char* con, void* data);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a left justified version of the string.
**    Parameters:      s:       target string to be justified.
**                     return:  left justified version of the string.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_ljust(const char* con, char ch);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Converts a string into lower case.
**    Parameters:      s:       target string to be converted.
**                     return:  new string of s which all chracters are lower case.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_lower(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Converts a string into upper case.
**    Parameters:      s:       target string to be converted.
**                     return:  new string of s which all chracters are upper case.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_upper(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a left trim version of the string.
**    Parameters:      s:       string to be lefft trimed.
**                     return:  new string with all left spaces are trimed.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_lstrip(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a right trim version of the string.
**    Parameters:      s:       string to be right trimed.
**                     return:  new string with all right spaces are trimed.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_rstrip(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a translation table to be used in translate().
**    Parameters:      k:       keys string.
**                     v:       values string.
**                     return:  translation table, TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_maketrans(const char* k, const char* v);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a translated string.
**    Parameters:      s:       string to be translated.
**                     data:    translation table.
**                     return:  translated string with data table.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_translate(const char* s, void* data);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a tuple where the string is parted into three parts.
**    Parameters:      s:       string to be parted.
**                     part:    substring used to depart s.
**                     return:  . TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_partition(const char* s, const char* part);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**    Parameters:      old:    to be replaced substring.
**                     new:    substring to replace the old ones.
**                     str:    original string.
**                     return: replaced string.
**    Created Date:    2022-10-05
**    Updated Date:    2022-11-09
***********************************************************************************************************************/
char* s_replace(const char* old, const char* new, const char* str);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Searches the string for a specified value and returns the last position of where it was found.
**    Parameters:      s:       full string to look for sub.
**                     sub:     target substring in s.
**                     return: the last occurs potion of the sub in s.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
unsigned int s_rfind(const char* s, const void* sub);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Searches the string for a specified value and returns the last position of where it was found.
**    Parameters:      s:       full string to look for sub.
**                     sub:     target substring in s.
**                     return: the last occurs potion of the sub in s.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
unsigned int s_rindex(const char* s, const void* sub);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a right justified version of the string.
**    Parameters:      s:       target string to be justified.
**                     return:  right justified version of the string.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_rjust(const char* con, char ch);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Returns a tuple where the string is parted into three parts. This method searches for the last
**                     occurrence of a specified string, and splits the string into a tuple containing three elements.
**    Parameters:      s:       string to be parted.
**                     part:    substring used to depart s.
**                     return:  . TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_rpartition(const char* s, const char* part);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Splits a string into a list, starting from the right.
**    Parameters:      s:       string to be splited.
**                     sep:     separator.
**                     max:     max amount of elements of the result list.
**                     return:  TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_rsplit(const char* s, const char* sep, unsigned max);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Splits a string into a list, starting from the right.
**    Parameters:      s:       string to be splited.
**                     sep:     separator.
**                     return:  TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_split(const char* s, const char* sep);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Splits the string at line breaks and returns a list.
**    Parameters:      s:       string to be splited.
**                     sep:     separator.
**                     return:  TODO: how to define the structure or returned value.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
void* s_splitlines(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     check if a string starts with a given substring.
**    Parameters:      pre:    prefix substring.
**                     s:      original string.
**                     return: true: str starts with pre, false: str does not start with pre.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
bool s_startswith(const char* pre, const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     trim space at the front and end of a string, return a copy.
**    Parameters:      s:    original string.
**                     return: trimmed string.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_strip(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Swaps cases, lower case becomes upper case and vice versa.
**    Parameters:      s:      original string.
**                     return: new string of s with lower case and upper case chracters are swaped.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_swapcase(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Converts the first character of each word to upper case.
**    Parameters:      s:      original string.
**                     return: new string of s with the first chracter of each word converted to upper case.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_title(const char* s);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Signature from Python: https://docs.python.org/3/library/stdtypes.html#string-methods
**                     Fills the string with a specified number of 0 values at the beginning
**    Parameters:      s:      original string.
**                     num:    number of zeros filled at th begginning of the s.
**                     return: new string of s with a specified number of 0 values at the beginning.
**    Created Date:    2024-01-17
**    Updated Date:    2024-01-17
***********************************************************************************************************************/
char* s_zfill(const char* s, unsigned num);

#endif //OPENFMT_STR_H
