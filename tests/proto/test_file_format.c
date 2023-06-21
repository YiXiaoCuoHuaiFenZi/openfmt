/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-03-21
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include "test_file_format.h"
#include "../macro.h"
#include "../../lib/memory.h"

int test_format_directory(char *malformed_file_directory, char *formatted_file_directory)
{
    List proto_files = CreateList();
    list_type_files(malformed_file_directory, "proto", proto_files);

    PtrToNode file_cur = proto_files->next;

    while (file_cur)
    {
        char *file_path = (char *) file_cur->data;
        printf("test formatting %s\n", file_path);

        Protobuf *proto = parse(file_path);

        proto->config.indentsUnit = 4;
        proto->config.alignByEqualSign = true;
        proto->config.topComment = false;
        proto->config.preview = false;

        unsigned int length_of_malformed_fp = strlen(file_path);

        unsigned actual_file_path_size = length_of_malformed_fp + strlen("_formatted.temp") + 1;
        char *actual_file_path = (char *) g_malloc(sizeof(char) * actual_file_path_size);
        strcat(actual_file_path, file_path);
        strcat(actual_file_path, "_formatted.temp");
        actual_file_path[actual_file_path_size - 1] = '\0';
        format_protobuf(proto, actual_file_path);

        unsigned expected_file_path_size = length_of_malformed_fp + strlen(".txt") + 1;
        char *expected_file_path_old = (char *) g_malloc(sizeof(char) * expected_file_path_size);
        strcat(expected_file_path_old, file_path);
        strcat(expected_file_path_old, ".txt");
        expected_file_path_old[expected_file_path_size - 1] = '\0';

        char *expected_file_path = replace("malformed", "formatted", expected_file_path_old);

        char *actual_text = read_text(actual_file_path);
        char *expected_text = read_text(expected_file_path);

        if (strcmp(actual_text, expected_text) != 0)
        {
            g_free(&actual_text);
            g_free(&expected_text);
            return TEST_FAIL;
        }

        free_protobuf(proto);
        g_free(&actual_file_path);
        g_free(&expected_file_path_old);
        g_free(&expected_file_path);
        file_cur = file_cur->next;
    }

    return TEST_SUCCESS;
}