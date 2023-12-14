/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Proto ADT(Abstract Data Type).
**    创建日期：    2022-10-03
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_PROTO_H
#define OPENFMT_PROTO_H

#include "../lib/g_list.h"
#include "../lib/linked_list.h"

typedef enum PositionStruct
{
	TOP,
	LEFT,
	BOTTOM,
	RIGHT
} PbPosition;

typedef struct CommentStruct
{
	char* text;
	PbPosition pos;
} PbComment;

typedef G_NodeTemplate(PbComment) PbCommentNode, PbCommentList;

typedef struct SyntaxStruct
{
	char* value;
	PbCommentList* comments;
} PbSyntax;

typedef struct PackageStruct
{
	char* value;
	PbCommentList* comments;
} PbPackage;

typedef struct ImportStruct
{
	char* value;
	PbCommentList* comments;
} PbImport;

typedef G_NodeTemplate(PbImport) PbImportNode, PbImportList;

typedef struct OptionStruct
{
	char* name;
	char* value;
	PbCommentList* comments;
} PbOption;

typedef G_NodeTemplate(PbOption) PbOptionNode, PbOptionList;

typedef struct ElementStruct
{
	char* label;
	char* type;
	char* name;
	char* number;
	char* annotation;
	PbCommentList* comments;
} PbElement;

typedef struct MessageElementStruct
{
	char* label;
	char* type;
	char* name;
	char* number;
	char* annotation;
	PbCommentList* comments;
} PbMessageElement;

typedef struct MessageStruct
{
	char* id;
	char* parent_id;
	char* parent_type;
	char* name;
	PbCommentList* comments;
	List elements;
} PbMessage;

typedef struct ExtendElementStruct
{
	char* label;
	char* type;
	char* name;
	char* number;
	char* annotation;
	PbCommentList* comments;
} PbExtendElement;

typedef struct ExtendStruct
{
	char* id;
	char* parent_id;
	char* parent_type;
	char* name;
	PbCommentList* comments;
	List elements;
} PbExtend;

typedef struct OneOfElementStruct
{
	char* label;
	char* type;
	char* name;
	char* number;
	char* annotation;
	PbCommentList* comments;
} PbOneOfElement;

typedef struct OneOfStruct
{
	char* id;
	char* parent_id;
	char* parent_type;
	char* name;
	PbCommentList* comments;
	List elements;
} PbOneOf;

typedef struct EnumElementStruct
{
	char* name;
	char* number;
	char* annotation;
	PbCommentList* comments;
} PbEnumElement;

typedef struct EnumStruct
{
	char* id;
	char* parent_id;
	char* parent_type;
	char* name;
	PbCommentList* comments;
	List elements;
} PbEnum;

typedef struct ServiceElementStruct
{
	char* label;
	char* name;
	char* request;
	char* response;
	PbCommentList* comments;
} PbServiceElement;

typedef struct ServiceStruct
{
	char* id;
	char* parent_id;
	char* parent_type;
	char* name;
	PbCommentList* comments;
	List elements;
} PbService;

typedef struct TextColorConfigStruct
{
	int default_color;
	int default_key_word;
	int syntax_key;
	int syntax_value;
	int package_key;
	int package_value;
	int option_key;
	int option_name;
	int option_value;
	int import_key;
	int import_value;
	int obj_key;
	int obj_name;
	int message_element_key;
	int message_element_label;
	int message_element_type;
	int message_element_name;
	int message_element_number;
	int message_element_annotation;
	int enum_element_name;
	int enum_element_number;
	int enum_element_annotation;
	int service_element_label;
	int service_element_name;
	int service_element_request;
	int service_element_response;
	int comment;
} PbTextColorConfig;

typedef struct ConfigStruct
{
	int indents_unit;
	bool align_by_equal_sign;
	bool top_comment;
	int max_comment_len;
	bool preview;
	PbTextColorConfig text_color_config;
} PbConfig;

typedef struct TextStruct
{
	char* text;
	int color;
} PbText;

typedef G_NodeTemplate(PbText) PbTextNode, PbTextList;

typedef struct ProtobufStruct
{
	PbSyntax* syntax;
	PbPackage* package;
	PbOptionList* options;
	// PbImport object list
	PbImportList* imports;
	// PbMessage, PbService, PbEnum object list
	List objects;
	PbTextList* colorful_text_list;
	PbConfig config;
	PbCommentList* comments;
} Protobuf;

typedef struct MessageElementLength
{
	// max string length from the element start to the equal sign.
	unsigned int max_name_len;
	// max string length from equal sign to the semicolon of the element.
	unsigned int max_value_len;
} MessageElementLength;

typedef struct EnumElementLength
{
	// max string length of enum element name.
	unsigned int max_name_len;
	// max string length from equal sign to the semicolon of the element.
	unsigned int max_value_len;
} EnumElementLength;

void print_text(PbText* text);

void print_text_list(PbTextList* text_list);

PbText* create_pb_text(char* text, int color);

void create_add_pb_text(char* text, int color, PbTextList* text_list);

bool has_top_comment(PbCommentList* comment_list);

bool has_right_comment(PbCommentList* comment_list);

bool has_bottom_comment(PbCommentList* comment_list);

void build_top_comment(
		PbCommentList* comment_list,
		int color,
		unsigned int indents,
		PbTextList* text_list,
		bool include_right_comment
);

void format_right_comment(PbCommentList* comment_list, int color, PbTextList* text_list);

void format_bottom_comment(PbCommentList* comment_list, int color, unsigned int indents, PbTextList* text_list);

void format_syntax(Protobuf* protobuf, PbTextList* text_list);

void format_package(Protobuf* protobuf, PbTextList* text_list);

void format_option(
		Protobuf* protobuf,
		PbOption* pb_option,
		unsigned int max_option_name_len,
		unsigned int max_option_value_len,
		PbTextList* text_list
);

unsigned int get_max_option_name_length(Protobuf* protobuf);

unsigned int get_max_option_value_length(Protobuf* protobuf);

void format_options(Protobuf* protobuf, PbTextList* text_list);

unsigned int get_max_import_value_length(Protobuf* protobuf);

void format_import(Protobuf* protobuf, PbImport* pb_import, unsigned int max_import_value_len, PbTextList* text_list);

void format_imports(Protobuf* protobuf, PbTextList* text_list);

MessageElementLength* get_max_message_element_lengths(List elements);

MessageElementLength* get_oneof_message_element_lengths(List elements);

void format_message_element(
		Protobuf* protobuf,
		PbMessageElement* ele,
		unsigned int indents,
		MessageElementLength* message_element_len_info,
		PbTextList* text_list
);

void format_message_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list);

void find_max_enum_element_length(List elements, EnumElementLength* enum_element_len_info);

void format_enum_element(
		Protobuf* protobuf,
		PbEnumElement* ele,
		unsigned int indents,
		EnumElementLength enum_element_len_info,
		PbTextList* text_list
);

void format_enum_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list);

void format_service_element(
		Protobuf* protobuf,
		PbServiceElement* ele,
		unsigned int indents,
		PbTextList* text_list
);

void format_service_elements(Protobuf* protobuf, List elements, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list);

void create_object_text(
		char* object_type,
		char* object_name,
		PbCommentList* object_comments,
		List object_elements,
		Protobuf* protobuf,
		unsigned int indents,
		MessageElementLength* lengths,
		PbTextList* text_list,
		void (* element_format_func)(Protobuf*, List, unsigned int, MessageElementLength*, PbTextList*)
);

void
format_object(Protobuf* protobuf, void* object, char* data_type, unsigned int indents, MessageElementLength* lengths,
		PbTextList* text_list);

void format_objects(Protobuf* protobuf, PbTextList* text_list);

void format_comments(Protobuf* protobuf, PbTextList* text_list);

void format_protobuf(Protobuf* protobuf, const char* file_path);

char* str_join(PbTextList* text_list);

void write_to_file(PbTextList* text_list, const char* file_path);

void free_PbText(PbTextNode* ptr);

void free_pb_message(PbMessage* obj);

void free_pb_enum(PbEnum* obj);

void free_pb_service(PbService* obj);

void free_pb_extend(PbExtend* obj);

void free_pb_oneof(PbOneOf* obj);

void free_pb_message_element(PbMessageElement* obj);

void free_pb_enum_element(PbEnumElement* obj);

void free_pb_service_element(PbServiceElement* obj);

/*
** the pointer to List(pointer to Node pointer), so we can free the List in method inner
*/
void free_objects(List* objects);

void free_protobuf(Protobuf* protobuf);

void free_comment_list(PbCommentList** comments);

#endif //OPENFMT_PROTO_H
