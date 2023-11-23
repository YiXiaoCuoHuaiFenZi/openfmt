/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    directory util function implementations.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "dir.h"
#include "memory.h"

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    check if a string path is a file or not.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
bool is_file(const char* path)
{
	struct stat path_state;
	stat(path, &path_state);
	int check = S_ISREG(path_state.st_mode);
	return check != 0;
}

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get file extension from absolutely path.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
const char* get_file_name_ext(const char* file_name)
{
	const char* dot = strrchr(file_name, '.');
	if (!dot || dot == file_name) return "";
	return dot + 1;
}

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get all files as a list which under the base path, including all sub directories.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void list_files(const char* base_path, List list)
{
	char temp_path[1000];
	struct dirent* p_dirent;
	DIR* dir = opendir(base_path);
	if (dir)
	{
		while ((p_dirent = readdir(dir)) != NULL)
		{
			if (strcmp(p_dirent->d_name, ".") != 0 && strcmp(p_dirent->d_name, "..") != 0)
			{
				strcpy(temp_path, base_path);
				strcat(temp_path, "/");
				strcat(temp_path, p_dirent->d_name);
				if (is_file(temp_path))
				{
					char* path = (char*)g_malloc(sizeof(temp_path) + 1);
					strcpy(path, temp_path);
					append_linked_list(path, "char", list);
				}
				else
				{
					list_files(temp_path, list);
				}
			}
		}
		closedir(dir);
	}
}

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    get all files with specified file type as a list which under the base path, including all sub
**                directories.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void list_type_files(const char* base_path, const char* extension, List list)
{
	char temp_path[1000];
	struct dirent* p_dirent;
	DIR* dir = opendir(base_path);
	if (dir)
	{
		while ((p_dirent = readdir(dir)) != NULL)
		{
			if (strcmp(p_dirent->d_name, ".") != 0 && strcmp(p_dirent->d_name, "..") != 0)
			{
				strcpy(temp_path, base_path);
				strcat(temp_path, "/");
				strcat(temp_path, p_dirent->d_name);
				if (is_file(temp_path))
				{
					const char* f_ext = get_file_name_ext(p_dirent->d_name);
					if (strcmp(f_ext, extension) == 0)
					{
						char* path = (char*)g_malloc(sizeof(temp_path) + 1);
						strcpy(path, temp_path);
						append_linked_list(path, "char", list);
					}
				}
				else
				{
					list_type_files(temp_path, extension, list);
				}
			}
		}
		closedir(dir);
	}
}

/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    print files in a list.
**    创建日期：    2022-10-02
**    更新日期：    2023-06-28
***********************************************************************************************************************/
void print_files(List list)
{
	PtrToNode p_node = list->next;
	while (p_node)
	{
		char* path = (char*)p_node->data;
		printf("%s\n", path);
		p_node = p_node->next;
	}
}
