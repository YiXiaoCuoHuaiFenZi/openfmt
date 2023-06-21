/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-03-21
**    更新日期：    2023-03-21
***********************************************************************************************************************/
#ifndef OPENFMT_FILE_H
#define OPENFMT_FILE_H

#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    read file as text, it returns a char pointer to the text content, must be released by calling free()
**                after using.
**    创建日期：    2023-03-21
**    更新日期：    2023-03-21
***********************************************************************************************************************/
char *read_text(const char *file_path);

#endif //OPENFMT_FILE_H
