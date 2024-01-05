/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#ifndef OPENFMT_DIR_H
#define OPENFMT_DIR_H

#include "linked_list.h"

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   check if a string path is a file or not.
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
bool is_file(const char* path);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get file extension from absolutely path.
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
const char* get_file_name_ext(const char* filename);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get all files as a list which under the base path, including all sub directories.
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
void list_files(const char* basePath, List list);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   get all files with specified file type as a list which under the base path, including all sub
**                     directories.
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
void list_type_files(const char* basePath, const char* extension, List list);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   print files in a list.
**    Created Date:    2022-10-02
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
void print_files(List list);

#endif //OPENFMT_DIR_H
