/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Proto ADT(Abstract Data Type).
**    Created Date:    2022-10-03
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "proto.h"
#include "comment_parser.h"
#include "../lib/str.h"
#include "../util/util.h"
#include "../lib/memory.h"

void print_text(PbText* text)
{
	print_text_with_color(text->text, text->color, false);
}

void print_text_list(PbTextList* text_list)
{
	PbTextNode* node = text_list->next;
	while (node)
	{
		PbText* text = (PbText*)(node->data);
		print_text(text);
		node = node->next;
	}
}

PbText* create_pb_text(char* text, int color)
{
	PbText* pb_text = (PbText*)g_malloc(sizeof(PbText));
	pb_text->text = text;
	pb_text->color = color;
	return pb_text;
}

void create_add_pb_text(char* text, int color, PbTextList* text_list)
{
	PbText* pb_text = create_pb_text(str_copy(text), color);
	append_list(PbTextNode, text_list, pb_text);
}

void format_protobuf(Protobuf* protobuf, const char* file_path)
{
	PbTextList* text_list = create_list(PbTextNode);
	format_syntax(protobuf, text_list);
	format_package(protobuf, text_list);
	format_options(protobuf, text_list);
	format_imports(protobuf, text_list);
	format_objects(protobuf, text_list);
	format_comments(protobuf, text_list);

	if (protobuf->config.preview)
	{
		print_text_list(text_list);
	}
	else
	{
		write_to_file(text_list, file_path);
	}

	dispose_list(PbTextNode, text_list, free_PbText);
}

char* str_join(PbTextList* text_list)
{
	unsigned long int length = 0;
	PbTextNode* node = text_list->next;
	while (node)
	{
		PbText* text = (PbText*)(node->data);
		length = length + strlen(text->text);
		node = node->next;
	}
	unsigned long int size = length;
	char* buff = (char*)g_malloc(sizeof(char) * size + 1);

	PbTextNode* cur = text_list->next;
	while (cur)
	{
		PbText* text = (PbText*)(cur->data);
		length = length + strlen(text->text);
		strcat(buff, text->text);
		cur = cur->next;
	}
	buff[size] = '\0';
	return buff;
}

void write_to_file(PbTextList* text_list, const char* file_path)
{
	FILE* fptr;
	fptr = fopen(file_path, "w");

	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	PbTextNode* node = text_list->next;
	while (node)
	{
		PbText* text = (PbText*)(node->data);
		fprintf(fptr, "%s", text->text);
		node = node->next;
	}

	fclose(fptr);
}

bool has_top_comment(PbCommentList* comment_list)
{
	PbCommentNode* cur = comment_list->next;
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

bool has_right_comment(PbCommentList* comment_list)
{
	PbCommentNode* cur = comment_list->next;
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

bool has_bottom_comment(PbCommentList* comment_list)
{
	PbCommentNode* cur = comment_list->next;
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
		PbCommentList* comment_list,
		int color,
		unsigned int indents,
		PbTextList* text_list,
		bool include_right_comment
)
{
	if (!has_top_comment(comment_list) && !has_right_comment(comment_list))
	{
		return;
	}

	PbCommentNode* cur = comment_list->next;

	if (has_top_comment(comment_list))
	{
		char* spaces = repeat(" ", indents);
		create_add_pb_text(spaces, color, text_list); // add indents
		g_free(to_void_ptr(&spaces));
		create_add_pb_text("/*\n", color, text_list);
	}
	else
	{
		if (has_right_comment(comment_list) && include_right_comment)
		{
			char* spaces = repeat(" ", indents);
			create_add_pb_text(spaces, color, text_list); // add indents
			g_free(to_void_ptr(&spaces));
			create_add_pb_text("/*\n", color, text_list);
		}
	}

	while (cur)
	{
		if (cur->data->pos == TOP)
		{
			char* spaces = repeat(" ", indents);
			create_add_pb_text(spaces, color, text_list); // add indents
			g_free(to_void_ptr(&spaces));
			if (strcmp(cur->data->text, "") == 0)
			{
				create_add_pb_text("**", color, text_list);
			}
			else
			{
				create_add_pb_text("**    ", color, text_list);
				create_add_pb_text(cur->data->text, color, text_list);
			}
			create_add_pb_text("\n", color, text_list);
		}
		cur = cur->next;
	}

	if (!include_right_comment)
	{
		if (has_top_comment(comment_list))
		{
			char* spaces = repeat(" ", indents);
			create_add_pb_text(spaces, color, text_list); // add indents
			g_free(to_void_ptr(&spaces));
			create_add_pb_text("*/\n", color, text_list);
			return;
		}
		return;
	}

	cur = comment_list->next;
	while (cur)
	{
		if (cur->data->pos == RIGHT)
		{
			char* spaces = repeat(" ", indents);
			create_add_pb_text(spaces, color, text_list); // add indents
			g_free(to_void_ptr(&spaces));
			if (strcmp(cur->data->text, "") == 0)
			{
				create_add_pb_text("**", color, text_list);
			}
			else
			{
				create_add_pb_text("**    ", color, text_list);
				create_add_pb_text(cur->data->text, color, text_list);
			}
			create_add_pb_text(cur->data->text, color, text_list);
			create_add_pb_text("\n", color, text_list);
		}
		cur = cur->next;
	}
	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	create_add_pb_text("*/\n", color, text_list);
}

void format_right_comment(PbCommentList* comment_list, int color, PbTextList* text_list)
{
	PbCommentNode* cur = comment_list->next;
	while (cur)
	{
		if (cur->data->pos == RIGHT)
		{
			create_add_pb_text("// ", color, text_list);
			create_add_pb_text(cur->data->text, color, text_list);
			return;
		}
		cur = cur->next;
	}
}

void format_bottom_comment(PbCommentList* comment_list, int color, unsigned int indents, PbTextList* text_list)
{
	if (!has_bottom_comment(comment_list))
	{
		return;
	}

	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	create_add_pb_text("/*\n", color, text_list);

	PbCommentNode* cur = comment_list->next;
	while (cur)
	{
		if (cur->data->pos == BOTTOM)
		{
			char* spacess = repeat(" ", indents);
			create_add_pb_text(spacess, color, text_list); // add indents
			g_free(to_void_ptr(&spacess));
			if (strcmp(cur->data->text, "") == 0)
			{
				create_add_pb_text("**", color, text_list);
			}
			else
			{
				create_add_pb_text("**    ", color, text_list);
				create_add_pb_text(cur->data->text, color, text_list);
			}
			create_add_pb_text(cur->data->text, color, text_list);
			create_add_pb_text("\n", color, text_list);
		}
		cur = cur->next;
	}
	char* spaces_end = repeat(" ", indents);
	create_add_pb_text(spaces_end, color, text_list); // add indents
	g_free(to_void_ptr(&spaces_end));
	create_add_pb_text("*/\n", color, text_list);
}

void format_syntax(Protobuf* protobuf, PbTextList* text_list)
{
	if (protobuf->syntax == NULL)
	{
		return;
	}
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(protobuf->syntax->comments, color_config.comment, 0, text_list, config.top_comment);
	create_add_pb_text("syntax", color_config.syntax_key, text_list);
	create_add_pb_text(" = ", color_config.default_color, text_list);
	create_add_pb_text(protobuf->syntax->value, color_config.syntax_value, text_list);
	create_add_pb_text(";", color_config.default_color, text_list);

	if (!config.top_comment && has_right_comment(protobuf->syntax->comments))
	{
		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(protobuf->syntax->comments, color_config.comment, text_list);
	}
	create_add_pb_text("\n\n", color_config.default_color, text_list);
}

void format_package(Protobuf* protobuf, PbTextList* text_list)
{
	if (protobuf->package == NULL)
	{
		return;
	}
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(protobuf->package->comments, color_config.comment, 0, text_list, config.top_comment);
	create_add_pb_text("package", color_config.package_key, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(protobuf->package->value, color_config.package_value, text_list);
	create_add_pb_text(";", color_config.default_color, text_list);

	if (!config.top_comment && has_right_comment(protobuf->package->comments))
	{
		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(protobuf->package->comments, color_config.comment, text_list);
	}
	create_add_pb_text("\n\n", color_config.default_color, text_list);
}

void format_option(
		Protobuf* protobuf,
		PbOption* pb_option,
		unsigned int max_option_name_len,
		unsigned int max_option_value_len,
		PbTextList* text_list
)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;
	build_top_comment(pb_option->comments, color_config.comment, 0, text_list, config.top_comment);

	create_add_pb_text("option", color_config.option_key, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(pb_option->name, color_config.option_name, text_list);

	// align by equal sign, fill extra spaces between the option name and equal sign.
	if (config.align_by_equal_sign)
	{
		unsigned int option_name_len = strlen(pb_option->name);
		unsigned int fill_space_amount = max_option_name_len - option_name_len;
		char* spaces = repeat(" ", fill_space_amount);
		create_add_pb_text(spaces, color_config.default_color, text_list);
		g_free(to_void_ptr(&spaces));
	}
	create_add_pb_text(" = ", color_config.default_color, text_list);
	create_add_pb_text(pb_option->value, color_config.option_value, text_list);
	create_add_pb_text(";", color_config.default_color, text_list);

	if (!config.top_comment && has_right_comment(pb_option->comments))
	{
		// align comments if align by equal sign, fill extra spaces between the option value and single line comment.
		if (config.align_by_equal_sign)
		{
			unsigned int option_value_len = strlen(pb_option->value);
			unsigned int fill_space_amount = max_option_value_len - option_value_len;
			char* spaces = repeat(" ", fill_space_amount);
			create_add_pb_text(spaces, color_config.default_color, text_list);
			g_free(to_void_ptr(&spaces));
		}

		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(pb_option->comments, color_config.comment, text_list);
	}
}

unsigned int get_max_option_name_length(Protobuf* protobuf)
{
	PbOptionNode* cur = protobuf->options->next;
	unsigned int max_len = 0;
	while (cur)
	{
		if (strlen(cur->data->name) > max_len)
		{
			max_len = strlen(cur->data->name);
		}
		cur = cur->next;
	}
	return max_len;
}

unsigned int get_max_option_value_length(Protobuf* protobuf)
{
	PbOptionNode* cur = protobuf->options->next;
	unsigned int max_len = 0;
	while (cur)
	{
		if (strlen(cur->data->value) > max_len)
		{
			max_len = strlen(cur->data->value);
		}
		cur = cur->next;
	}
	return max_len;
}

void format_options(Protobuf* protobuf, PbTextList* text_list)
{
	if (protobuf->options == NULL)
	{
		return;
	}
	PbTextColorConfig color_config = protobuf->config.text_color_config;
	unsigned int max_option_name_len = get_max_option_name_length(protobuf);
	unsigned int max_option_value_len = get_max_option_value_length(protobuf);

	PbOptionNode* cur = protobuf->options->next;
	while (cur)
	{
		format_option(protobuf, cur->data, max_option_name_len, max_option_value_len, text_list);
		create_add_pb_text("\n", color_config.default_color, text_list);
		cur = cur->next;
	}
	create_add_pb_text("\n", color_config.default_color, text_list);
}

unsigned int get_max_import_value_length(Protobuf* protobuf)
{
	PbImportNode* cur = protobuf->imports->next;
	unsigned int max_len = 0;
	while (cur)
	{
		if (strlen(cur->data->value) > max_len)
		{
			max_len = strlen(cur->data->value);
		}
		cur = cur->next;
	}
	return max_len;
}

void format_import(Protobuf* protobuf, PbImport* pb_import, unsigned int max_import_value_len, PbTextList* text_list)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(pb_import->comments, color_config.comment, 0, text_list, config.top_comment);
	create_add_pb_text("import", color_config.import_key, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(pb_import->value, color_config.import_value, text_list);
	create_add_pb_text(";", color_config.default_color, text_list);

	if (!config.top_comment && has_right_comment(pb_import->comments))
	{
		unsigned int import_value_len = strlen(pb_import->value);
		unsigned int fill_space_amount = max_import_value_len - import_value_len;
		char* spaces = repeat(" ", fill_space_amount);
		create_add_pb_text(spaces, color_config.default_color, text_list);
		g_free(to_void_ptr(&spaces));
		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(pb_import->comments, color_config.comment, text_list);
	}
}

void format_imports(Protobuf* protobuf, PbTextList* text_list)
{
	if (protobuf->imports == NULL)
	{
		return;
	}
	PbTextColorConfig color_config = protobuf->config.text_color_config;
	unsigned int max_import_value_len = get_max_import_value_length(protobuf);

	PbImportNode* cur = protobuf->imports->next;
	while (cur)
	{
		format_import(protobuf, cur->data, max_import_value_len, text_list);
		create_add_pb_text("\n", color_config.default_color, text_list);
		cur = cur->next;
	}
	create_add_pb_text("\n", color_config.default_color, text_list);
}


void get_max_message_element_lengths(List elements, MessageElementLength* lengths)
{
	lengths->max_name_len = 0;
	lengths->max_value_len = 0;

	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbMessageElement") == 0)
		{
			PbMessageElement* ele = (PbMessageElement*)cur->data;

			unsigned int len1 = strlen(ele->type) + strlen(ele->name);
			if (ele->label)
			{
				len1 = strlen(ele->label) + strlen(ele->type) + strlen(ele->name);
				len1++; // additional space between label and type.
			}
			if (len1 > lengths->max_name_len)
			{
				lengths->max_name_len = len1;
			}

			unsigned int len2 = strlen(ele->number);
			if (ele->annotation)
			{
				len2 = strlen(ele->number) + strlen(ele->annotation);
				len2++; // additional space between number and annotation.
			}
			if (len2 > lengths->max_value_len)
			{
				lengths->max_value_len = len2;
			}
		}
		cur = cur->next;
	}
}

void get_oneof_message_element_lengths(List elements, MessageElementLength* lengths)
{
	lengths->max_name_len = 0;
	lengths->max_value_len = 0;
	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbOneOf") == 0)
		{
			PbOneOf* oneof = (PbOneOf*)cur->data;
			MessageElementLength one_of_ele_lengths;
			get_max_message_element_lengths(oneof->elements, &one_of_ele_lengths);
			if (lengths->max_name_len < one_of_ele_lengths.max_name_len)
				lengths->max_name_len = one_of_ele_lengths.max_name_len;

			if (lengths->max_value_len < one_of_ele_lengths.max_value_len)
				lengths->max_value_len = one_of_ele_lengths.max_value_len;
		}
		cur = cur->next;
	}
}

void format_message_element(
		Protobuf* protobuf,
		PbMessageElement* ele,
		unsigned int indents,
		MessageElementLength* lengths,
		PbTextList* text_list
)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(ele->comments, color_config.comment, indents, text_list, config.top_comment);

	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color_config.default_color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	unsigned int cmlbes = strlen(ele->type) + strlen(ele->name); // max_name_len of current element.
	if (ele->label)
	{
		cmlbes = strlen(ele->label) + strlen(ele->type) + strlen(ele->name);
		cmlbes++; // additional space between label and type.

		create_add_pb_text(ele->label, color_config.message_element_label, text_list);
		create_add_pb_text(" ", color_config.default_color, text_list);
	}
	create_add_pb_text(ele->type, color_config.message_element_type, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(ele->name, color_config.message_element_name, text_list);

	// align by equal sign, fill extra spaces between the element name and equal sign.
	if (config.align_by_equal_sign)
	{
		unsigned int fill_space_amount = lengths->max_name_len - cmlbes;
		char* spacess = repeat(" ", fill_space_amount);
		create_add_pb_text(spacess, color_config.default_color, text_list);
		g_free(to_void_ptr(&spacess));
	}

	create_add_pb_text(" = ", color_config.default_color, text_list);
	create_add_pb_text(ele->number, color_config.message_element_number, text_list);

	unsigned int cmlbesas = strlen(ele->number); // max_value_len of current element.
	if (ele->annotation)
	{
		create_add_pb_text(" ", color_config.default_color, text_list);

		cmlbesas = strlen(ele->number) + strlen(ele->annotation);
		cmlbesas++; // additional space between number and annotation.

		create_add_pb_text(ele->annotation, color_config.message_element_annotation, text_list);
		create_add_pb_text(";", color_config.default_color, text_list);
	}
	else
	{
		create_add_pb_text(";", color_config.default_color, text_list);
	}

	if (!config.top_comment && has_right_comment(ele->comments))
	{
		unsigned int space_amount = 2; // make sure there are two spaces between semicolon and single line comment
		if (config.align_by_equal_sign)
		{
			space_amount += lengths->max_value_len - cmlbesas;
		}
		char* spacess = repeat(" ", space_amount);
		create_add_pb_text(spacess, color_config.default_color, text_list);
		g_free(to_void_ptr(&spacess));
		format_right_comment(ele->comments, color_config.comment, text_list);
	}

	create_add_pb_text("\n", color_config.default_color, text_list);
}

void format_message_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list)
{
	MessageElementLength common_ele_lengths;
	MessageElementLength oneof_ele_lengths;
	MessageElementLength final_lengths;
	get_max_message_element_lengths(elements, &common_ele_lengths);
	get_oneof_message_element_lengths(elements, &oneof_ele_lengths);
	final_lengths.max_name_len = common_ele_lengths.max_name_len;
	final_lengths.max_value_len = common_ele_lengths.max_value_len;

	int indents_unit = protobuf->config.indents_unit;

	// if lengths is not NULL, it is the parent all elements max lengths all OneOf elements.
	if (lengths != NULL && lengths->max_name_len != 0)
	{
		if (final_lengths.max_name_len + indents_unit < lengths->max_name_len)
			final_lengths.max_name_len = lengths->max_name_len - indents_unit;

		if (final_lengths.max_value_len + indents_unit < lengths->max_value_len)
			final_lengths.max_value_len = lengths->max_value_len;
	}
	else
	{
		// if max length of oneof elements is greater than the max length of common message elements, use max length of elements of oneof.
		if (final_lengths.max_name_len < oneof_ele_lengths.max_name_len + indents_unit)
			final_lengths.max_name_len = oneof_ele_lengths.max_name_len + indents_unit;

		if (final_lengths.max_value_len < oneof_ele_lengths.max_value_len)
			final_lengths.max_value_len = oneof_ele_lengths.max_value_len;
	}

	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbMessageElement") == 0)
		{
			PbMessageElement* ele = (PbMessageElement*)cur->data;
			format_message_element(protobuf, ele, indents, &final_lengths, text_list);
		}
		else if (strcmp(cur->data_type, "PbOneOf") == 0)
		{
			format_object(protobuf, cur->data, cur->data_type, indents, &final_lengths, text_list);
		}
		else
		{
			format_object(protobuf, cur->data, cur->data_type, indents, NULL, text_list);
		}
		cur = cur->next;
	}
}


void find_max_enum_element_length(List elements, EnumElementLength* message_element_len_info)
{
	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbEnumElement") == 0)
		{
			PbEnumElement* ele = (PbEnumElement*)cur->data;

			if (strlen(ele->name) > message_element_len_info->max_name_len)
			{
				message_element_len_info->max_name_len = strlen(ele->name);
			}

			unsigned int len = strlen(ele->number);
			if (ele->annotation)
			{
				len = strlen(ele->number) + strlen(ele->annotation);
				len++; // additional space between number and annotation.
			}
			if (len > message_element_len_info->max_value_len)
			{
				message_element_len_info->max_value_len = len;
			}
		}
		cur = cur->next;
	}
}

void format_enum_element(
		Protobuf* protobuf,
		PbEnumElement* ele,
		unsigned int indents,
		EnumElementLength eeli,
		PbTextList* text_list
)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(ele->comments, color_config.comment, indents, text_list, config.top_comment);

	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color_config.default_color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	create_add_pb_text(ele->name, color_config.enum_element_name, text_list);

	// align by equal sign, fill extra spaces between the element name and equal sign.
	if (config.align_by_equal_sign)
	{
		char* spacess = repeat(" ", eeli.max_name_len - strlen(ele->name));
		create_add_pb_text(spacess, color_config.default_color, text_list);
		g_free(to_void_ptr(&spacess));
	}

	create_add_pb_text(" = ", color_config.default_color, text_list);
	create_add_pb_text(ele->number, color_config.enum_element_number, text_list);

	unsigned int cmlbesas = strlen(ele->number); // max_value_len of current element.
	if (ele->annotation)
	{
		create_add_pb_text(" ", color_config.default_color, text_list);

		cmlbesas = strlen(ele->number) + strlen(ele->annotation);
		cmlbesas++; // additional space between number and annotation.

		create_add_pb_text(ele->annotation, color_config.enum_element_annotation, text_list);
		create_add_pb_text(";", color_config.default_color, text_list);
	}
	else
	{
		create_add_pb_text(";", color_config.default_color, text_list);
	}


	if (!config.top_comment && has_right_comment(ele->comments))
	{
		unsigned int space_amount = eeli.max_value_len - cmlbesas;
		space_amount = space_amount + 2; // make sure there are two spaces between semicolon and single line comment
		char* spacess = repeat(" ", space_amount);
		create_add_pb_text(spacess, color_config.default_color, text_list);
		g_free(to_void_ptr(&spacess));
		format_right_comment(ele->comments, color_config.comment, text_list);
	}

	create_add_pb_text("\n", color_config.default_color, text_list);
}

void format_enum_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list)
{
	EnumElementLength eeli = { 0, 0 };

	find_max_enum_element_length(elements, &eeli);

	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbEnumElement") == 0)
		{
			PbEnumElement* ele = (PbEnumElement*)cur->data;
			format_enum_element(protobuf, ele, indents, eeli, text_list);
		}
		cur = cur->next;
	}
}

void format_service_element(
		Protobuf* protobuf,
		PbServiceElement* ele,
		unsigned int indents,
		PbTextList* text_list
)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(ele->comments, color_config.comment, indents, text_list, config.top_comment);
	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color_config.default_color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	create_add_pb_text(ele->label, color_config.service_element_label, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(ele->name, color_config.service_element_name, text_list);
	create_add_pb_text(" (", color_config.default_color, text_list);
	create_add_pb_text(ele->request, color_config.service_element_request, text_list);
	create_add_pb_text(")", color_config.default_color, text_list);
	create_add_pb_text(" returns ", color_config.service_element_label, text_list);
	create_add_pb_text("(", color_config.default_color, text_list);
	create_add_pb_text(ele->response, color_config.service_element_response, text_list);
	create_add_pb_text(");", color_config.default_color, text_list);
	if (!config.top_comment && has_right_comment(ele->comments))
	{
		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(ele->comments, color_config.comment, text_list);
	}
	create_add_pb_text("\n", color_config.default_color, text_list);
}

void format_service_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list)
{
	List cur = elements->next;
	while (cur)
	{
		if (strcmp(cur->data_type, "PbServiceElement") == 0)
		{
			PbServiceElement* ele = (PbServiceElement*)cur->data;
			format_service_element(protobuf, ele, indents, text_list);
		}
		cur = cur->next;
	}
}

void create_object_text(
		char* object_type,
		char* object_name,
		PbCommentList* object_comments,
		List object_elements,
		Protobuf* protobuf,
		unsigned int indents,
		MessageElementLength* lengths,
		PbTextList* text_list,
		void (element_format_func)(Protobuf*, List, unsigned int, MessageElementLength*, PbTextList*)
)
{
	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	build_top_comment(object_comments, color_config.comment, indents, text_list, config.top_comment);
	char* spaces = repeat(" ", indents);
	create_add_pb_text(spaces, color_config.default_color, text_list); // add indents
	g_free(to_void_ptr(&spaces));
	create_add_pb_text(object_type, color_config.obj_key, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text(object_name, color_config.obj_name, text_list);
	create_add_pb_text(" ", color_config.default_color, text_list);
	create_add_pb_text("{", color_config.default_color, text_list);

	if (!config.top_comment && has_right_comment(object_comments))
	{
		create_add_pb_text("  ", color_config.default_color, text_list);
		format_right_comment(object_comments, color_config.comment, text_list);
	}
	create_add_pb_text("\n", color_config.default_color, text_list);
	element_format_func(protobuf, object_elements, indents + config.indents_unit, lengths, text_list);
	format_bottom_comment(object_comments, color_config.comment, indents + config.indents_unit, text_list);
	char* spaces_bottom = repeat(" ", indents);
	create_add_pb_text(spaces_bottom, color_config.default_color, text_list); // add indents
	g_free(to_void_ptr(&spaces_bottom));
	create_add_pb_text("}\n", color_config.default_color, text_list);
}

void
format_object(Protobuf* protobuf, void* object, char* data_type, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list)
{
	if (strcmp(data_type, "PbMessage") == 0)
	{
		PbMessage* obj = (PbMessage*)object;
		create_object_text(
				"message",
				obj->name,
				obj->comments,
				obj->elements,
				protobuf,
				indents,
				lengths,
				text_list,
				format_message_elements
		);
		return;
	}

	if (strcmp(data_type, "PbEnum") == 0)
	{
		PbEnum* obj = (PbEnum*)object;
		create_object_text(
				"enum",
				obj->name,
				obj->comments,
				obj->elements,
				protobuf,
				indents,
				lengths,
				text_list,
				format_enum_elements
		);
		return;
	}

	if (strcmp(data_type, "PbService") == 0)
	{
		PbEnum* obj = (PbEnum*)object;
		create_object_text(
				"service",
				obj->name,
				obj->comments,
				obj->elements,
				protobuf,
				indents,
				lengths,
				text_list,
				format_service_elements
		);
		return;
	}

	if (strcmp(data_type, "PbOneOf") == 0)
	{
		PbOneOf* obj = (PbOneOf*)object;
		create_object_text(
				"oneof",
				obj->name,
				obj->comments,
				obj->elements,
				protobuf,
				indents,
				lengths,
				text_list,
				format_message_elements
		);
		return;
	}

	if (strcmp(data_type, "PbExtend") == 0)
	{
		PbMessage* obj = (PbMessage*)object;
		create_object_text(
				"extend",
				obj->name,
				obj->comments,
				obj->elements,
				protobuf,
				indents,
				lengths,
				text_list,
				format_message_elements
		);
		return;
	}
}

void format_objects(Protobuf* protobuf, PbTextList* text_list)
{
	PbTextColorConfig color_config = protobuf->config.text_color_config;
	List cur = protobuf->objects->next;
	while (cur)
	{
		format_object(protobuf, cur->data, cur->data_type, 0, NULL, text_list);
		if (cur->next)
		{
			create_add_pb_text("\n", color_config.default_color, text_list);
		}
		cur = cur->next;
	}
}


void format_comments(Protobuf* protobuf, PbTextList* text_list)
{
	if (protobuf->comments == NULL)
		return;

	PbConfig config = protobuf->config;
	PbTextColorConfig color_config = protobuf->config.text_color_config;

	int indents = config.indents_unit;

	// convert all comments as bottom comments
	PbCommentNode* cur = protobuf->comments->next;
	create_add_pb_text("/*\n", color_config.default_color, text_list);
	while (cur)
	{
		if (cur->data->pos == BOTTOM)
		{
			create_add_pb_text("**", color_config.comment, text_list);
			char* spaces = repeat(" ", indents);
			create_add_pb_text(spaces, color_config.default_color, text_list); // add indents
			g_free(to_void_ptr(&spaces));
			create_add_pb_text(cur->data->text, color_config.comment, text_list);
			create_add_pb_text("\n", color_config.default_color, text_list);
		}
		cur = cur->next;
	}
	create_add_pb_text("*/", color_config.comment, text_list);
	create_add_pb_text("\n", color_config.default_color, text_list);
}

void free_comment_list(PbCommentList** comments)
{
	dispose_list(PbCommentList, (*comments), free_PbComment);
}

void free_PbText(PbTextNode* ptr)
{
	PbText* t = (PbText*)(ptr->data);
	g_free(to_void_ptr(&t->text));
	g_free(to_void_ptr(&t));
}

void free_pb_message(PbMessage* obj)
{
	g_free(to_void_ptr(&obj->id));
	g_free(to_void_ptr(&obj->parent_id));
	g_free(to_void_ptr(&obj->name));
	free_comment_list(&obj->comments);
	free_objects(&obj->elements);
	g_free(to_void_ptr(&obj));
}

void free_pb_enum(PbEnum* obj)
{
	g_free(to_void_ptr(&obj->id));
	g_free(to_void_ptr(&obj->name));
	free_comment_list(&obj->comments);
	free_objects(&obj->elements);
	g_free(to_void_ptr(&obj));
}

void free_pb_service(PbService* obj)
{
	g_free(to_void_ptr(&obj->id));
	g_free(to_void_ptr(&obj->name));
	free_comment_list(&obj->comments);
	free_objects(&obj->elements);
	g_free(to_void_ptr(&obj));
}

void free_pb_extend(PbExtend* obj)
{
	g_free(to_void_ptr(&obj->id));
	g_free(to_void_ptr(&obj->name));
	free_comment_list(&obj->comments);
	free_objects(&obj->elements);
	g_free(to_void_ptr(&obj));
}

void free_pb_oneof(PbOneOf* obj)
{
	g_free(to_void_ptr(&obj->id));
	g_free(to_void_ptr(&obj->name));
	g_free(to_void_ptr(&obj->parent_id));
	free_comment_list(&obj->comments);
	free_objects(&obj->elements);
	g_free(to_void_ptr(&obj));
}

void free_pb_message_element(PbMessageElement* obj)
{
	g_free(to_void_ptr(&obj->label));
	g_free(to_void_ptr(&obj->type));
	g_free(to_void_ptr(&obj->name));
	g_free(to_void_ptr(&obj->number));
	g_free(to_void_ptr(&obj->annotation));
	free_comment_list(&obj->comments);
	g_free(to_void_ptr(&obj));
}

void free_pb_enum_element(PbEnumElement* obj)
{
	g_free(to_void_ptr(&obj->name));
	g_free(to_void_ptr(&obj->number));
	g_free(to_void_ptr(&obj->annotation));
	free_comment_list(&obj->comments);
	g_free(to_void_ptr(&obj));
}

void free_pb_service_element(PbServiceElement* obj)
{
	g_free(to_void_ptr(&obj->label));
	g_free(to_void_ptr(&obj->name));
	g_free(to_void_ptr(&obj->request));
	g_free(to_void_ptr(&obj->response));
	free_comment_list(&obj->comments);
	g_free(to_void_ptr(&obj));
}

void free_objects(List* object_list)
{

	List head = *object_list;
	List cur = head->next;

	while (cur != NULL)
	{
		PtrToLinkedListNode temp_node = cur;
		cur = cur->next;

		char* data_type = temp_node->data_type;

		if (strcmp(data_type, "PbMessage") == 0)
		{
			PbMessage* obj = temp_node->data;
			free_pb_message(obj);
		}

		if (strcmp(data_type, "PbEnum") == 0)
		{
			PbEnum* obj = temp_node->data;
			free_pb_enum(obj);
		}

		if (strcmp(data_type, "PbService") == 0)
		{
			PbService* obj = temp_node->data;
			free_pb_service(obj);
		}

		if (strcmp(data_type, "PbExtend") == 0)
		{
			PbExtend* obj = temp_node->data;
			free_pb_extend(obj);
		}

		if (strcmp(data_type, "PbOneOf") == 0)
		{
			PbOneOf* obj = temp_node->data;
			free_pb_oneof(obj);
		}

		if (strcmp(data_type, "PbMessageElement") == 0)
		{
			PbMessageElement* obj = temp_node->data;
			free_pb_message_element(obj);
		}

		if (strcmp(data_type, "PbEnumElement") == 0)
		{
			PbEnumElement* obj = temp_node->data;
			free_pb_enum_element(obj);
		}

		if (strcmp(data_type, "PbServiceElement") == 0)
		{
			PbServiceElement* obj = temp_node->data;
			free_pb_service_element(obj);
		}

		g_free(to_void_ptr(&temp_node->data_type));
		g_free(to_void_ptr(&temp_node));
	}
	g_free(to_void_ptr(&head));
}

void free_protobuf(Protobuf* protobuf)
{
	if (protobuf->syntax != NULL)
	{
		g_free(to_void_ptr(&protobuf->syntax->value));
		free_comment_list(&protobuf->syntax->comments);
		g_free(to_void_ptr(&protobuf->syntax));
	}

	if (protobuf->package != NULL)
	{
		g_free(to_void_ptr(&protobuf->package->value));
		free_comment_list(&protobuf->package->comments);
		g_free(to_void_ptr(&protobuf->package));
	}

	if (protobuf->options)
	{
		PbOptionNode* head = protobuf->options;
		PbOptionNode* cur = head->next;
		while (cur)
		{
			PbOptionNode* t_node = cur;
			cur = cur->next;
			g_free(to_void_ptr(&t_node->data->name));
			g_free(to_void_ptr(&t_node->data->value));
			free_comment_list(&t_node->data->comments);
			g_free(to_void_ptr(&t_node->data));
			g_free(to_void_ptr(&t_node));
		}
		g_free(to_void_ptr(&head));
	}

	if (protobuf->imports != NULL)
	{
		PbImportNode* head = protobuf->imports;
		PbImportNode* cur = head->next;
		while (cur)
		{
			PbImportNode* t_node = cur;
			cur = cur->next;
			g_free(to_void_ptr(&t_node->data->value));
			free_comment_list(&t_node->data->comments);
			g_free(to_void_ptr(&t_node->data));
			g_free(to_void_ptr(&t_node));
		}
		g_free(to_void_ptr(&head));
	}
	free_objects(&protobuf->objects);
	if (protobuf->comments != NULL)
	{
		free_comment_list(&protobuf->comments);
	}
	g_free(to_void_ptr(&protobuf));
}