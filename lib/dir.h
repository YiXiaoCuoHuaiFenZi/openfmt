/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_DIR_H
#define OPENFMT_DIR_H

#include "linked_list.h"

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    check if a string path is a file or not.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
bool is_file(const char* path);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get file extension from absolutely path.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
const char* get_file_name_ext(const char* filename);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get all files as a list which under the base path, including all sub directories.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void list_files(const char* basePath, List list);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get all files with specified file type as a list which under the base path, including all sub
**                directories.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void list_type_files(const char* basePath, const char* extension, List list);

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    print files in a list.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void print_files(List list);

#endif //OPENFMT_DIR_H
