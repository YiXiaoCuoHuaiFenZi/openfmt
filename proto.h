/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Proto ADT(Abstract Data Type).
**    创建日期：    2022-10-03
**    更新日期：    2023-03-17
***********************************************************************************************************************/
#ifndef OPENFMT_PROTO_H
#define OPENFMT_PROTO_H

#include "lib/g_list.h"
#include "lib/linked_list.h"

typedef enum PositionStruct
{
    TOP,
    LEFT,
    BOTTOM,
    RIGHT
} PbPosition;

typedef struct CommentStruct
{
    char *text;
    PbPosition pos;
} PbComment;

typedef G_NodeTemplate(PbComment) PbCommentNode, PbCommentList;

typedef struct SyntaxStruct
{
    char *value;
    PbCommentList *comments;
} PbSyntax;

typedef struct PackageStruct
{
    char *value;
    PbCommentList *comments;
} PbPackage;

typedef struct ImportStruct
{
    char *value;
    PbCommentList *comments;
} PbImport;

typedef G_NodeTemplate(PbImport) PbImportNode, PbImportList;

typedef struct OptionStruct
{
    char *name;
    char *value;
    PbCommentList *comments;
} PbOption;

typedef G_NodeTemplate(PbOption) PbOptionNode, PbOptionList;

typedef struct ElementStruct
{
    char *label;
    char *type;
    char *name;
    char *number;
    char *annotation;
    PbCommentList *comments;
} PbElement;

typedef struct MessageElementStruct
{
    char *label;
    char *type;
    char *name;
    char *number;
    char *annotation;
    PbCommentList *comments;
} PbMessageElement;

typedef struct MessageStruct
{
    char *id;
    char *parentId;
    char *name;
    PbCommentList *comments;
    List elements;
} PbMessage;

typedef struct ExtendElementStruct
{
    char *label;
    char *type;
    char *name;
    char *number;
    char *annotation;
    PbCommentList *comments;
} PbExtendElement;

typedef struct ExtendStruct
{
    char *id;
    char *parentId;
    char *name;
    PbCommentList *comments;
    List elements;
} PbExtend;

typedef struct OneOfElementStruct
{
    char *label;
    char *type;
    char *name;
    char *number;
    char *annotation;
    PbCommentList *comments;
} PbOneOfElement;

typedef struct OneOfStruct
{
    char *id;
    char *parentId;
    char *name;
    PbCommentList *comments;
    List elements;
} PbOneOf;

typedef struct EnumElementStruct
{
    char *name;
    char *number;
    char *annotation;
    PbCommentList *comments;
} PbEnumElement;

typedef struct EnumStruct
{
    char *id;
    char *parentId;
    char *name;
    PbCommentList *comments;
    List elements;
} PbEnum;

typedef struct ServiceElementStruct
{
    char *label;
    char *name;
    char *request;
    char *response;
    PbCommentList *comments;
} PbServiceElement;

typedef struct ServiceStruct
{
    char *id;
    char *parentId;
    char *name;
    PbCommentList *comments;
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
    int indentsUnit;
    bool alignByEqualSign;
    bool topComment;
    int commentMaxLength;
    bool preview;
    PbTextColorConfig textColorConfig;
} PbConfig;

typedef struct TextStruct
{
    char *text;
    int color;
} PbText;

typedef G_NodeTemplate(PbText) PbTextNode, PbTextList;

typedef struct ProtobufStruct
{
    PbSyntax *syntax;
    PbPackage *package;
    PbOptionList *options;
    /*
    ** PbImport object list
    */
    PbImportList *imports;
    /*
    **  PbMessage, PbService, PbEnum object list
    */
    List objects;
    PbTextList *colorfulTextList;
    PbConfig config;
    PbCommentList *comments;
} Protobuf;

typedef struct MessageElementLengthInfo
{
    unsigned int maxLengthBeforeEqualSign;
    unsigned int maxLengthBetweenEqualSignAndSemicolon;
} MessageElementLengthInfo;

typedef struct EnumElementLengthInfo
{
    unsigned int maxLengthOfName;
    unsigned int maxLengthBetweenEqualSignAndSemicolon;
} EnumElementLengthInfo;

void print_text(PbText *text);

void print_text_list(PbTextList *textList);

PbText *create_pb_text(char *text, int color);

void create_add_pb_text(char *text, int color, PbTextList *textList);

bool has_top_comment(PbCommentList *commentList);

bool has_right_comment(PbCommentList *commentList);

bool has_bottom_comment(PbCommentList *commentList);

void build_top_comment(
        PbCommentList *commentList,
        int color,
        unsigned int indents,
        PbTextList *textList,
        bool includeRightComment
);

void format_right_comment(PbCommentList *commentList, int color, PbTextList *textList);

void format_bottom_comment(PbCommentList *commentList, int color, unsigned int indents, PbTextList *textList);

void format_syntax(Protobuf *protobuf, PbTextList *textList);

void format_package(Protobuf *protobuf, PbTextList *textList);

void format_option(
        Protobuf *protobuf,
        PbOption *pbOption,
        unsigned int maxOptionNameLength,
        unsigned int maxOptionValueLength,
        PbTextList *textList
);

unsigned int get_max_option_name_length(Protobuf *protobuf);

unsigned int get_max_option_value_length(Protobuf *protobuf);

void format_options(Protobuf *protobuf, PbTextList *textList);

unsigned int get_max_import_value_length(Protobuf *protobuf);

void format_import(Protobuf *protobuf, PbImport *pbImport, unsigned int maxImportValueLength, PbTextList *textList);

void format_imports(Protobuf *protobuf, PbTextList *textList);

void get_max_message_element_length(List elements, MessageElementLengthInfo *meli);

void format_message_element(
        Protobuf *protobuf,
        PbMessageElement *ele,
        unsigned int indents,
        MessageElementLengthInfo messageElementLengthInfo,
        PbTextList *textList
);

void format_message_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList);

void find_max_enum_element_length(List elements, EnumElementLengthInfo *enumElementLengthInfo);

void format_enum_element(
        Protobuf *protobuf,
        PbEnumElement *ele,
        unsigned int indents,
        EnumElementLengthInfo enumElementLengthInfo,
        PbTextList *textList
);

void format_enum_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList);

void format_service_element(
        Protobuf *protobuf,
        PbServiceElement *ele,
        unsigned int indents,
        PbTextList *textList
);

void format_service_elements(Protobuf *protobuf, List elements, unsigned int indents, PbTextList *textList);

void create_object_text(
        char *objectTypeName,
        char *objectName,
        PbCommentList *objectComments,
        List objectElements,
        Protobuf *protobuf,
        unsigned int indents,
        PbTextList *textList,
        void (*ElementFormatFunc)(Protobuf *, List, unsigned int, PbTextList *)
);

void format_object(Protobuf *protobuf, void *object, char *data_type, unsigned int indents, PbTextList *textList);

void format_objects(Protobuf *protobuf, PbTextList *textList);

void format_comments(Protobuf *protobuf, PbTextList *textList);

void format_protobuf(Protobuf *protobuf, const char *filePath);

char *str_join(PbTextList *textList);

void write_to_file(PbTextList *textList, const char *filePath);

void free_PbText(PbTextNode *ptr);

void free_pb_message(PbMessage *obj);

void free_pb_enum(PbEnum *obj);

void free_pb_service(PbService *obj);

void free_pb_extend(PbExtend *obj);

void free_pb_oneof(PbOneOf *obj);

void free_pb_message_element(PbMessageElement *obj);

void free_pb_enum_element(PbEnumElement *obj);

void free_pb_service_element(PbServiceElement *obj);

/*
 * the pointer to List(pointer to Node pointer), so we can free the List in method inner
 */
void free_objects(List *objects);

void free_protobuf(Protobuf *protobuf);

void free_comment_list(PbCommentList **comments);

#endif //OPENFMT_PROTO_H
