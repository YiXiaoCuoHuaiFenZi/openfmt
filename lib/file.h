/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   utils to handble files.
**    Created Date:    2023-03-21
**    Updated Date:    2023-03-21
***********************************************************************************************************************/
#ifndef OPENFMT_FILE_H
#define OPENFMT_FILE_H

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   read file as text, it returns a char pointer to the text content, must be released by calling
**                     free() after using.
**    Parameters:      file_path: the path of the file to be read.
**                     return: the text content of file.
**    Created Date:    2023-03-21
**    Updated Date:    2023-03-21
***********************************************************************************************************************/
char* read_text(const char* file_path);

#endif //OPENFMT_FILE_H
