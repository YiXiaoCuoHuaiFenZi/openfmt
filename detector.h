/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-07
**    更新日期：    2022-10-07
***********************************************************************************************************************/
#ifndef OPENFMT_DETECTOR_H
#define OPENFMT_DETECTOR_H

#include <stdbool.h>

typedef enum PbTypeEnum
{
	Syntax,
	Package,
	Option,
	Import,
	Message,
	Enum,
	Service,
	Extend,
	MessageElement,
	ExtendElement,
	EnumElement,
	ServiceElement,
	OneOf,
	Unknown
} PbType;

bool is_syntax(char* line);

bool is_package(char* line);

bool is_option(char* line);

bool is_import(char* line);

bool is_message(char* line);

bool is_enum(char* line);

bool is_service(char* line);

bool is_extend(char* line);

bool is_element(char* line);

bool is_message_element(char* line);

bool is_map_element(char* line);

bool is_enum_element(char* line);

bool is_service_element(char* line);

bool is_extend_element(char* line);

bool is_oneof(char* line);

PbType get_pb_type(char* line);

#endif //OPENFMT_DETECTOR_H
