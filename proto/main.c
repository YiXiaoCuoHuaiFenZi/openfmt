/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Program entrance.
**    创建日期：    2022-09-30
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include <dirent.h>
#include "proto_parser.h"
#include "../lib/dir.h"
#include "../lib/file.h"
#include "../lib/memory.h"

const char* VERSION = "1.0.0";

enum Mode
{
	FILE_MODE,
	DIRECTORY_MODE
};

typedef struct Config
{
	PbConfig* pb_config;
	enum Mode mode;
	char* proto_file_path;
	char* proto_directory;
} Config;

const char* get_version();

void check_help_command(const char* command);

void no_option_value(const char* actual_option, const char* expected_option);

void parse_commands(int argc, char* argv[], Config* config);

const char* usage_message();

void run(Config* config);

void free_char(char* data);

int main(int argc, char* argv[])
{
	PbConfig pb_config;
	pb_config.indents_unit = 4;
	pb_config.align_by_equal_sign = true;
	pb_config.top_comment = false;
	pb_config.max_comment_len = 10000;
	pb_config.preview = false;

	Config config;
	config.pb_config = &pb_config;
	config.proto_file_path = NULL;
	config.proto_directory = NULL;

	parse_commands(argc, argv, &config);
	run(&config);

	return 0;
}

const char* usage_message()
{
	const char* usage = "****************************************************************************************************\n"
						"*                                     Protobuf file formatter                                      *\n"
						"*                                           MIT License                                            *\n"
						"****************************************************************************************************\n"
						"usage:\n"
						"  openfmt -f [filepath] or -d [file_folder] [option=<value>]\n"
						"\n"
						"mandatory:\n"
						"  -f                           single file model, format the specified proto file.\n"
						"  -d                           folder model, will format proto files under the specified folder and\n"
						"                               all sub-folders.\n"
						"options:\n"
						"  --preview                    preview formatted protobuf file(s) with syntax highlighting in\n"
						"                               terminal or command line window. choices: [true, false], default\n"
						"                               value is false, if it set to true, protobuf file(s) will not be\n"
						"                               overwritten by formatted one(s).\n"
						"  --indents                    the number of indented spaces, default is 4.\n"
						"  --top-comment                convert single line comment at the right of the code line to top\n"
						"                               comment(above the code line), choices: [true, false], default value\n"
						"                               is false.\n"
						"  --align-by-equal-sign        align the code by equal sign. choices: [true, false], default\n"
						"                               is true.\n"
						"version:\n"
						"  -v                           show current version of openfmt.\n"
						"  --version                    show current version of openfmt.\n"
						"help:\n"
						"  -h                           show this help message and exit.\n"
						"  --help                       show this help message and exit.\n";

	return usage;
}

void no_option_value(const char* actual_option, const char* expected_option)
{
	if (strcmp(actual_option, expected_option) == 0)
	{
		printf("The value of --%s is not set.\n\n", actual_option);
		printf("Please type -h or --help to get help information.\n");
		exit(EXIT_FAILURE);
	}
}

void check_help_command(const char* command)
{
	const char* usage = usage_message();
	if ((strcmp(command, "-h") == 0) || (strcmp(command, "--help") == 0))
	{
		printf("%s", usage);
		exit(EXIT_SUCCESS);
	}
}

void check_version_command(const char* command)
{
	if ((strcmp(command, "-v") == 0) || (strcmp(command, "--version") == 0))
	{
		printf("%s\n", get_version());
		exit(EXIT_SUCCESS);
	}
}

void parse_commands(int argc, char* argv[], Config* config)
{
	const char* usage = usage_message();
	if (argc == 1)
	{
		printf("%s", usage);
		exit(EXIT_SUCCESS);
	}

	bool has_mandatory_command = false;
	for (int arg_index = 1; arg_index < argc; arg_index++)
	{
		check_help_command(argv[arg_index]);
		check_version_command(argv[arg_index]);

		if (argv[arg_index][0] == '-' && argv[arg_index][1] != '-') // mandatory commands.
		{
			if (strlen(&argv[arg_index][1]) != 1)
			{
				printf("Unrecognized command: %s, type -h or --help to get help information.\n", argv[arg_index]);
				exit(EXIT_SUCCESS);
			}

			switch (argv[arg_index][1])
			{
			case 'f':
			{
				int next_index = arg_index + 1;
				if (next_index >= argc)
				{
					printf("Missing proto file path, type -h or --help to get help information\n");
					exit(EXIT_FAILURE);
				}
				config->mode = FILE_MODE;
				config->proto_file_path = argv[next_index];
				arg_index = next_index;
				has_mandatory_command = true;
				break;
			}
			case 'd':
			{
				int next_index = arg_index + 1;
				if (next_index >= argc)
				{
					printf("%s", "Missing proto file directory, type -h or --help to get help information.\n");
					exit(EXIT_SUCCESS);
				}
				config->mode = DIRECTORY_MODE;
				config->proto_directory = argv[next_index];
				arg_index = next_index;
				has_mandatory_command = true;
				break;
			}
			default:
				printf("Unrecognized command: %s, type -h or --help to get help information.\n", argv[arg_index]);
				exit(EXIT_SUCCESS);
			}
		}
		else if (argv[arg_index][0] == '-' && argv[arg_index][1] == '-')  // options commands and help command.
		{
			char* command = argv[arg_index];
			const char* has_value = strstr(command, "=");
			if (has_value == NULL)
			{
				if (!has_mandatory_command)
				{
					printf("No mandatory command, type -h or --help to get help information.\n");
					exit(EXIT_FAILURE);
				}

				const char* option = replace("--", "", command);
				if ((strcmp(option, "preview") != 0) && (strcmp(option, "indents") != 0) &&
					(strcmp(option, "top-comment") != 0) && (strcmp(option, "align-by-equal-sign") != 0) &&
					(strcmp(option, "help") != 0))
				{
					printf("Unrecognized option: %s, type -h or --help to get help information.\n", option);
					exit(EXIT_FAILURE);
				}
				// check values for all options then exit.
				no_option_value(option, "preview");
				no_option_value(option, "indents");
				no_option_value(option, "top-comment");
				no_option_value(option, "align-by-equal-sign");
			}
			else
			{
				char* option = sub_str_between_str(command, "--", "=");
				char* tmp = strstr(command, "=");
				char* value = trim_prefix(tmp, "=");

				if (strcmp(option, "preview") == 0) // parse preview optional command
				{
					if (strcmp(value, "true") == 0)
					{
						config->pb_config->preview = true;
					}
					else if (strcmp(value, "false") == 0)
					{
						config->pb_config->preview = false;
					}
					else
					{
						printf("%s", "invalid preview value, type -h or --help to get help information.\n");
						exit(EXIT_FAILURE);
					}
				}
				else if (strcmp(option, "indents") == 0) // parse preview optional command
				{
					if (atoi(value) == 0)
					{
						printf("%s", "invalid preview value, type -h or --help to get help information.\n");
						exit(EXIT_FAILURE);
					}

					config->pb_config->indents_unit = atoi(value);
				}
				else if (strcmp(option, "top-comment") == 0) // parse preview optional command
				{
					if (strcmp(value, "true") == 0)
					{
						config->pb_config->top_comment = true;
					}
					else if (strcmp(value, "false") == 0)
					{
						config->pb_config->top_comment = false;
					}
					else
					{
						printf("%s", "invalid top_comment value, type -h or --help to get help information.\n");
						exit(EXIT_FAILURE);
					}
				}
				else if (strcmp(option, "align-by-equal-sign") == 0) // parse preview optional command
				{
					if (strcmp(value, "true") == 0)
					{
						config->pb_config->align_by_equal_sign = true;
					}
					else if (strcmp(value, "false") == 0)
					{
						config->pb_config->align_by_equal_sign = false;
					}
					else
					{
						printf("%s", "invalid align-by-equal-sign value, type -h or --help to get help information.\n");
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					printf("Unrecognized option: %s, type -h or --help to get help information.\n", option);
					exit(EXIT_FAILURE);
				}
				g_free(to_void_ptr(&option));
				g_free(to_void_ptr(&value));
			}
		}
		else
		{
			printf("Unrecognized command: %s, type -h or --help to get help information.\n", argv[arg_index]);
			exit(EXIT_SUCCESS);
		}
	}

	if (config->proto_file_path == NULL && config->proto_directory == NULL)
	{
		printf("Target file or folder is not set, please use\n"
			   "-f to specify the target file or\n"
			   "-d to specify the target folder.\n\n"
			   "type -h or --help to get help information.\n");
		exit(EXIT_FAILURE);
	}
}

const char* get_version()
{
	return VERSION;
}

void free_char(char* data)
{
	g_free(to_void_ptr(&data));
}

void run(Config* config)
{
	List proto_files = create_linked_list();
	if (config->mode == FILE_MODE)
	{
		if (!is_file(config->proto_file_path))
		{
			printf("Cannot open file %s\n", config->proto_file_path);
			exit(EXIT_FAILURE);
		}

		append_linked_list(str_copy(config->proto_file_path), "char", proto_files);
	}
	else if (config->mode == DIRECTORY_MODE)
	{
		DIR* dir = opendir(config->proto_directory);
		if (dir == NULL)
		{
			printf("Cannot open directory %s\n", config->proto_directory);
			exit(EXIT_FAILURE);
		}
		closedir(dir);
		list_type_files(config->proto_directory, "proto", proto_files);
	}

	PtrToLinkedListNode file_cur = proto_files->next;

	while (file_cur)
	{
		char* file_path = (char*)file_cur->data;
		printf("formatting %s\n", file_path);
		Protobuf* proto = parse(file_path);
		/*
		** override default value of indents, align_by_equal_sign, top_comment and preview.
		*/
		proto->config.indents_unit = config->pb_config->indents_unit;
		proto->config.align_by_equal_sign = config->pb_config->align_by_equal_sign;
		proto->config.top_comment = config->pb_config->top_comment;
		proto->config.preview = config->pb_config->preview;

		format_protobuf(proto, file_path);
		free_protobuf(proto);
		file_cur = file_cur->next;
	}
	dispose_linked_list(proto_files, (void (*)(void*))free_char);
}
