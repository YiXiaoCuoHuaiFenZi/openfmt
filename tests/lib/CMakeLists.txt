cmake_minimum_required(VERSION 3.23)
project(openfmt-lib-tester)

set(CMAKE_C_STANDARD 99)

enable_testing()

# tests for str
add_test(NAME test_str_copy COMMAND openfmt-lib-tester test_str_copy)
add_test(NAME test_trim COMMAND openfmt-lib-tester test_trim)
add_test(NAME test_trim_prefix COMMAND openfmt-lib-tester test_trim_prefix)
add_test(NAME test_trim_suffix COMMAND openfmt-lib-tester test_trim_suffix)
add_test(NAME test_trim_pre_suf COMMAND openfmt-lib-tester test_trim_pre_suf)
add_test(NAME test_starts_with COMMAND openfmt-lib-tester test_starts_with)
add_test(NAME test_ends_with COMMAND openfmt-lib-tester test_ends_with)
add_test(NAME test_replace COMMAND openfmt-lib-tester test_replace)
add_test(NAME test_char_to_binary_str COMMAND openfmt-lib-tester test_char_to_binary_str)
add_test(NAME test_int_to_binary_str COMMAND openfmt-lib-tester test_int_to_binary_str)
add_test(NAME test_char_to_binary_str_with_space COMMAND openfmt-lib-tester test_char_to_binary_str_with_space)
add_test(NAME test_str_to_hex_str COMMAND openfmt-lib-tester test_str_to_hex_str)
add_test(NAME test_bytes_to_hex_str COMMAND openfmt-lib-tester test_bytes_to_hex_str)
add_test(NAME test_repeat COMMAND openfmt-lib-tester test_repeat)
add_test(NAME test_pick_str_until COMMAND openfmt-lib-tester test_pick_str_until)

# tests for g_list
add_test(NAME test_G_NodeTemplate_int COMMAND openfmt-lib-tester test_G_NodeTemplate_int)
add_test(NAME test_G_NodeTemplate_char COMMAND openfmt-lib-tester test_G_NodeTemplate_char)
add_test(NAME test_create_list COMMAND openfmt-lib-tester test_create_list)
add_test(NAME test_append_list COMMAND openfmt-lib-tester test_append_list)
add_test(NAME test_is_empty_list COMMAND openfmt-lib-tester test_is_empty_list)
add_test(NAME test_dispose_list COMMAND openfmt-lib-tester test_dispose_list)

# tests for dir
add_test(NAME test_is_file COMMAND openfmt-lib-tester test_is_file)
add_test(NAME test_list_files COMMAND openfmt-lib-tester test_list_files)
add_test(NAME test_print_files COMMAND openfmt-lib-tester test_print_files)

# tests for uuid
add_test(NAME test_random_bytes COMMAND openfmt-lib-tester test_random_bytes)
add_test(NAME test_uuid4 COMMAND openfmt-lib-tester test_uuid4)

# test for hash table
add_test(NAME test_hash_table COMMAND openfmt-lib-tester test_hash_table)
