/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Message, Enum, Service, Extend.
**    创建日期：    2022-11-14
**    更新日期：    2023-06-20
***********************************************************************************************************************/
#include <string.h>
#include "comment_parser.h"
#include "detector.h"
#include "package_parser.h"
#include "option_parser.h"
#include "lib/str_queue.h"
#include "import_parser.h"
#include "message_parser.h"
#include "message_ele_parser.h"
#include "object_parser.h"
#include "enum_parser.h"
#include "service_parser.h"
#include "extend_parser.h"
#include "oneof_parser.h"
#include "enum_ele_parser.h"
#include "service_ele_parser.h"
#include "lib/g_hash_table.h"
#include "lib/str.h"
#include "lib/memory.h"

void append_as_bottom_comments(PbCommentList *comments, PbCommentList *bottomComments)
{
    PbCommentNode *cur = bottomComments->next;
    while (cur)
    {
        PbComment *pbComment = cur->data;
        pbComment->pos = BOTTOM;
        /*
        ** create a total new comment data, and append it to the target comments list, so we can release bottomComments
        ** by calling dispose_list.
        */
        PbComment *new_comment = (PbComment *) malloc(sizeof(PbComment));
        memcpy(new_comment, pbComment, sizeof(PbComment));
        new_comment->text = str_copy(pbComment->text);
        // append the new comment data to the comments list.
        append_list(PbCommentNode, comments, new_comment);
        cur = cur->next;
    }
}

void update_current_obj_comments(State *state, PbCommentList *bottomComments)
{
    if (strcmp(state->current_obj_type, "PbMessage") == 0)
    {
        PbMessage *current_obj = (PbMessage *) (state->current_obj);
        append_as_bottom_comments(current_obj->comments, bottomComments);
        return;
    }
    if (strcmp(state->current_obj_type, "PbEnum") == 0)
    {
        PbEnum *current_obj = (PbEnum *) (state->current_obj);
        append_as_bottom_comments(current_obj->comments, bottomComments);
        return;
    }
    if (strcmp(state->current_obj_type, "PbOneOf") == 0)
    {
        PbOneOf *current_obj = (PbOneOf *) (state->current_obj);
        append_as_bottom_comments(current_obj->comments, bottomComments);
        return;
    }
    if (strcmp(state->current_obj_type, "PbExtend") == 0)
    {
        PbExtend *current_obj = (PbExtend *) (state->current_obj);
        append_as_bottom_comments(current_obj->comments, bottomComments);
        return;
    }
}

char *get_parent_id(State *state)
{
    if (strcmp(state->current_obj_type, "PbMessage") == 0)
    {
        PbMessage *parent = (PbMessage *) (state->current_obj);
        return str_copy(parent->id);
    }
    if (strcmp(state->current_obj_type, "PbEnum") == 0)
    {
        PbEnum *parent = (PbEnum *) (state->current_obj);
        return str_copy(parent->id);
    }
    if (strcmp(state->current_obj_type, "PbOneOf") == 0)
    {
        PbOneOf *parent = (PbOneOf *) (state->current_obj);
        return str_copy(parent->id);
    }
    if (strcmp(state->current_obj_type, "PbExtend") == 0)
    {
        PbExtend *parent = (PbExtend *) (state->current_obj);
        return str_copy(parent->id);
    }

    return NULL;
}

List get_parent_elements(State *state)
{
    if (strcmp(state->current_obj_type, "PbMessage") == 0)
    {
        PbMessage *parent = (PbMessage *) (state->current_obj);
        return parent->elements;
    }
    if (strcmp(state->current_obj_type, "PbEnum") == 0)
    {
        PbEnum *parent = (PbEnum *) (state->current_obj);
        return parent->elements;
    }
    if (strcmp(state->current_obj_type, "PbOneOf") == 0)
    {
        PbOneOf *parent = (PbOneOf *) (state->current_obj);
        return parent->elements;
    }
    if (strcmp(state->current_obj_type, "PbExtend") == 0)
    {
        PbExtend *parent = (PbExtend *) (state->current_obj);
        return parent->elements;
    }

    return NULL;
}

void current_obj_to_parent_obj(State *state)
{
    if (strcmp(state->current_obj_type, "PbMessage") == 0)
    {
        PbMessage *parent = (PbMessage *) (state->current_obj);
        state->parent_obj = parent;
        state->parent_obj_type = "PbMessage";
        return;
    }
    if (strcmp(state->current_obj_type, "PbEnum") == 0)
    {
        PbEnum *parent = (PbEnum *) (state->current_obj);
        state->parent_obj = parent;
        state->parent_obj_type = "PbEnum";
        return;
    }
    if (strcmp(state->current_obj_type, "PbOneOf") == 0)
    {
        PbOneOf *parent = (PbOneOf *) (state->current_obj);
        state->parent_obj = parent;
        state->parent_obj_type = "PbOneOf";
        return;
    }
    if (strcmp(state->current_obj_type, "PbExtend") == 0)
    {
        PbExtend *parent = (PbExtend *) (state->current_obj);
        state->parent_obj = parent;
        state->parent_obj_type = "PbExtend";
        return;
    }
}

void parent_obj_to_current_obj(State *state)
{
    if (strcmp(state->parent_obj_type, "PbMessage") == 0)
    {
        PbMessage *current_obj = (PbMessage *) (state->current_obj);
        state->current_obj = GHashTableGet(current_obj->parentId, state->obj_dic);
        state->current_obj_type = "PbMessage";
        return;
    }
    if (strcmp(state->parent_obj_type, "PbEnum") == 0)
    {
        PbEnum *current_obj = (PbEnum *) (state->current_obj);
        state->current_obj = GHashTableGet(current_obj->parentId, state->obj_dic);
        state->current_obj_type = "PbEnum";
        return;
    }
    if (strcmp(state->parent_obj_type, "PbOneOf") == 0)
    {
        PbOneOf *current_obj = (PbOneOf *) (state->current_obj);
        state->current_obj = GHashTableGet(current_obj->parentId, state->obj_dic);
        state->current_obj_type = "PbOneOf";
        return;
    }
    if (strcmp(state->parent_obj_type, "PbExtend") == 0)
    {
        PbExtend *current_obj = (PbExtend *) (state->current_obj);
        state->current_obj = GHashTableGet(current_obj->parentId, state->obj_dic);
        state->current_obj_type = "PbExtend";
        return;
    }
}

void parse_object(Protobuf *protobuf, SQueue lineQueue, PbCommentList *topComments, State *state)
{
    if (IsEmptySQueue(lineQueue))
    {
        return;
    }

    if (topComments == NULL)
    {
        topComments = make_top_comments(lineQueue);
    }

    char *line = str_copy(lineQueue->head->str);
    char *tmp = trim(line);
    if (strstr(tmp, "}") && starts_with("}", tmp))
    {
        DeSQueue(lineQueue);
        state->r_brace++;
        /*
        ** There are comments exist at bottom of the message:
        ** message Test {
        **     string header = 1;// header
        **     // message inner bottom
        **     //message inner bottom bottombottombottombottom
        ** }
        **/
        if (topComments != NULL)
        {
            update_current_obj_comments(state, topComments);
            /*
            ** the topComments is bottom comments actually, and the comment value data will be added to the object,
            ** so we must release this extra list data.
            */
            free_comment_list(&topComments);
        }

        if (state->l_brace == state->r_brace)
        {
            g_free(&tmp);
            g_free(&line);
            return;
        }

        if (state->parent_obj != NULL)
        {
            parent_obj_to_current_obj(state);
        }
    }
    g_free(&tmp);

    PbType pbType = get_pb_type(line);

    switch (pbType)
    {
        case Message:
        {
            PbMessage *obj = parse_pb_message(line, lineQueue, topComments);
            if (state->current_obj != NULL)
            {
                obj->parentId = get_parent_id(state);
                AppendList(obj, "PbMessage", get_parent_elements(state));
                current_obj_to_parent_obj(state);
            } else
            {
                AppendList(obj, "PbMessage", protobuf->objects);
            }
            state->l_brace++;
            state->current_obj = obj;
            state->current_obj_type = "PbMessage";
            GHashTablePut(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
            break;
        }
        case Enum:
        {
            PbEnum *obj = parse_pb_enum(line, lineQueue, topComments);
            if (state->current_obj != NULL)
            {
                obj->parentId = get_parent_id(state);
                AppendList(obj, "PbEnum", get_parent_elements(state));
                current_obj_to_parent_obj(state);
            } else
            {
                AppendList(obj, "PbEnum", protobuf->objects);
            }
            state->l_brace++;
            state->current_obj = obj;
            state->current_obj_type = "PbEnum";
            GHashTablePut(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
            break;
        }
        case Service:
        {
            PbService *obj = parse_pb_service(line, lineQueue, topComments);
            state->l_brace++;
            state->current_obj = obj;
            state->current_obj_type = "PbService";
            AppendList(obj, "PbService", protobuf->objects);
            break;
        }
        case Extend:
        {
            PbExtend *obj = parse_pb_extend(line, lineQueue, topComments);
            if (state->current_obj != NULL)
            {
                obj->parentId = get_parent_id(state);
                AppendList(obj, "PbExtend", get_parent_elements(state));
                current_obj_to_parent_obj(state);
            } else
            {
                AppendList(obj, "PbExtend", protobuf->objects);
            }
            state->l_brace++;
            state->current_obj = obj;
            state->current_obj_type = "PbExtend";
            GHashTablePut(obj->id, state->current_obj_type, obj, NULL, state->obj_dic);
            break;
        }
        case OneOf:
        {
            PbOneOf *obj = parse_pb_oneof(line, lineQueue, topComments);
            if (state->current_obj != NULL)
            {
                obj->parentId = get_parent_id(state);
                AppendList(obj, "PbOneOf", get_parent_elements(state));
                current_obj_to_parent_obj(state);
            }

            state->l_brace++;
            state->current_obj = obj;
            state->current_obj_type = "PbOneOf";
            break;
        }
            // The element of Message, OneOf and Extend has the same structure, so can be used by all of them.
        case MessageElement:
        {
            PbMessageElement *element = parse_pb_message_element(line, topComments, lineQueue);
            PbMessage *obj = (PbMessage *) (state->current_obj);
            AppendList(element, "PbMessageElement", obj->elements);
            break;
        }
        case EnumElement:
        {
            PbEnumElement *element = parse_pb_enum_element(line, topComments, lineQueue);
            PbEnum *obj = (PbEnum *) (state->current_obj);
            AppendList(element, "PbEnumElement", obj->elements);
            break;
        }
        case ServiceElement:
        {
            PbServiceElement *element = parse_pb_service_element(line, topComments, lineQueue);
            PbService *obj = (PbService *) (state->current_obj);
            AppendList(element, "PbServiceElement", obj->elements);
            break;
        }
        default:
        {
            break;
        }
    }
    g_free(&line);
    parse_object(protobuf, lineQueue, NULL, state);
}