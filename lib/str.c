/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   generic methods to handle string.
**    Created Date:    2022-10-05
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "str.h"
#include "memory.h"

char* str_copy(const char* str)
{
	unsigned int size = strlen(str) + 1;
	char* result = (char*)g_malloc(size);
	memcpy(result, str, size);
	return result;
}

char* trim(const char* str)
{
	if (str == NULL)
		return NULL;

	unsigned int len = strlen(str);

	// trim leading space
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)  // All spaces?
	{
		char* result = (char*)g_malloc(1);
		result[0] = '\0';
		return result;
	}

	// trim trailing space
	const char* end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))end--;
	end++;

	// set output size to minimum of trimmed string length and buffer size minus 1
	unsigned int out_size = (end - str) < len - 1 ? (end - str) : len - 1;
	if ((end - str) == len) // no space at the start and end of the string.
	{
		out_size = len;
	}

	char* result = (char*)g_malloc(out_size + 1);
	memcpy(result, str, out_size);
	result[out_size] = '\0';

	return result;
}

char* trim_prefix(const char* str, const char* prefix)
{
	unsigned int str_len = strlen(str);
	unsigned int prefix_len = strlen(prefix);
	if (str_len < prefix_len || prefix_len == 0)
	{
		return str_copy(str);
	}

	unsigned int str_index = 0;
	while (str_index < str_len)
	{
		unsigned int match_index;
		for (match_index = 0; match_index < prefix_len && str[str_index + match_index + 1]; match_index++)
		{
			if (str[str_index + match_index] != prefix[match_index])
				break;
		}
		if (match_index == prefix_len)
		{
			str_index += prefix_len;
		}
		else
			break;
	}

	return str_copy(str + str_index);
}

char* trim_suffix(const char* str, const char* suffix)
{
	unsigned int str_len = strlen(str);
	unsigned int suffix_len = strlen(suffix);
	if (str_len < suffix_len || suffix_len == 0)
	{
		return str_copy(str);
	}

	unsigned int index = str_len;
	const char* str_end = str + strlen(str) - 1;
	const char* suffix_end = suffix + strlen(suffix) - 1;
	unsigned int match_time = 0;
	while (index > 0)
	{
		unsigned int mached_count = 0;
		while (*str_end == *suffix_end)
		{
			str_end--;
			suffix_end--;
			index--;
			mached_count++;
		}
		if (mached_count == strlen(suffix))
		{
			suffix_end = suffix + strlen(suffix) - 1;
			match_time++;
		}
		else
			break;
	}

	unsigned int size = str_len - suffix_len * match_time + 1;
	char* result = (char*)g_malloc(size);
	memcpy(result, str, str_len - strlen(str_end + 1));
	result[size - 1] = '\0';
	return result;
}

char* trim_pre_suf(const char* str, const char* substr)
{
	char* s = trim_prefix(str, substr);
	char* r = trim_suffix(s, substr);
	g_free(to_void_ptr(&s));
	return r;
}

bool starts_with(const char* pre, const char* str)
{
	size_t len_pre = strlen(pre);
	size_t len_str = strlen(str);
	return len_str < len_pre ? false : memcmp(pre, str, len_pre) == 0;
}

bool ends_with(const char* suffix, const char* str)
{
	if (!str || !suffix)
		return true;

	size_t len = strlen(str);
	size_t len_suffix = strlen(suffix);
	return len_suffix > len ? false : memcmp(str + len - len_suffix, suffix, len_suffix) == 0;
}

char* replace(const char* old, const char* new, const char* str)
{
	int count = 0;
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (!strncmp(str + i, old, strlen(old)))
		{
			// 找到目标字符串， 计数一次
			i += strlen(old) - 1;
			count++;
		}
	}

	unsigned int buffer_size = strlen(str) + count * (strlen(new) - strlen(old)) + 1;
	char* replaced = (char*)g_malloc(buffer_size);
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (!strncmp(str + i, old, strlen(old))) //查找目标字符串
		{
			// 找到目标字符串
			strcat(replaced, new);
			i += strlen(old) - 1;
		}
		else
		{
			strncat(replaced, str + i, 1);            //保存一字节进缓冲区
		}
	}
	replaced[buffer_size - 1] = '\0';
	return replaced;
}

char* sub_str_between_str(const char* str, const char* start, const char* end)
{
	char* s = str_copy(str);
	char* has_start = strstr(s, start);
	if (has_start == NULL)
		return NULL;

	char* has_end = strstr(s, end);
	if (has_end == NULL)
		return NULL;

	char* start_s = strstr(s, start) + strlen(start);
	char* end_s = strstr(s, end);

	unsigned int size = end_s - start_s + 1;
	char* v = (char*)g_malloc(size);
	memcpy(v, start_s, end_s - start_s);
	v[end_s - start_s] = '\0'; // must ends with '\0'
	g_free(to_void_ptr(&s));

	return v;
}

char* char_to_binary_str(char ch)
{
	char* r = (char*)g_malloc(9);
	for (int i = 7; i >= 0; --i)
	{
		r[7 - i] = (ch & (1 << i)) ? '1' : '0';
	}
	r[8] = '\0';
	return r;
}

char* int_to_binary_str(int value)
{
	char* pointer = (char*)&value;

	int len = sizeof(value);
	char* r = (char*)g_malloc(len * 8 + 1);
	int index = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		for (int j = 7; j >= 0; --j)
		{
			r[index] = (pointer[i] & (1 << j)) ? '1' : '0';
			index++;
		}
	}
	r[len * 8] = '\0';
	return r;
}

char* char_to_binary_str_with_space(const char* str)
{
	unsigned long str_len = strlen(str);                       // original string length.
	unsigned long space_amount = str_len - 1;                     // the space separator amount between each character.
	unsigned long zero_end = 1;                                   // the last end zero character amount.
	unsigned long size = (str_len + space_amount) * 8 + zero_end; // total size of output binary string.
	char* r = (char*)g_malloc(size);

	int index = 0;
	for (int i = 0; i < str_len; i++)
	{
		for (int j = 7; j >= 0; --j)
		{
			r[index] = (str[i] & (1 << j)) ? '1' : '0';
			index++;
		}
		if (index < (str_len) * 8)
		{
			r[index] = ' ';
			index++;
		}
	}
	r[size - 1] = '\0';
	return r;
}

void str_to_hex_str(const char* input, char* output)
{
	// TODO: have memory overflow bugs, refer error in https://stackoverflow.com/questions/52420160/ios-error-heap-corr
	//  uption-detected-free-list-is-damaged-and-incorrect-guard-v#comment100895932_52429784
	int loop = 0;
	int i = 0;

	while (input[loop] != '\0')
	{
		sprintf((char*)(output + i), "%02x", input[loop]);
		loop += 1;
		i += 2;
	}
	output[i++] = '\0';
}

char* bytes_to_hex_str(const byte input[], int len)
{
	int size = (len * 2) + 1;
	char* output = (char*)g_malloc(size);
	for (int i = 0; i < len; i++)
	{
		sprintf(&output[i * 2], "%02x", input[i]);
	}
	output[size - 1] = '\0';
	return output;
}

char* repeat(const char* s, unsigned int times)
{
	unsigned int len = strlen(s);
	unsigned int size = len * times + 1;
	char* r = (char*)g_malloc(size);
	char* cur = r;
	for (int i = 0; i < times; i++)
	{
		memcpy(cur, s, len);
		cur = cur + len;
	}
	r[size - 1] = '\0';

	return r;
}

char* pick_str_until(const char* s, char ch, bool include)
{
	int i = 0;

	bool found = false;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			found = true;
			i++;  // index start from 0, so increase 1 when found the charactor.
			break;
		}
		i++;
	}

	if (!found)
	{
		return NULL;
	}

	if (include)
	{
		char* r = (char*)g_malloc(i + 1);
		memcpy(r, s, i);
		r[i] = '\0';
		return r;
	}
	else
	{
		char* r = (char*)g_malloc(i);
		memcpy(r, s, i - 1);
		r[i - 1] = '\0';
		return r;
	}
}