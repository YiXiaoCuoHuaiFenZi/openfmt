cmake_minimum_required(VERSION 3.23)
project(openfmt C)

set(CMAKE_C_STANDARD 99)

add_executable(openfmt
        proto/main.c
        proto/proto.c
        proto/proto.h
        proto/proto_parser.c
        proto/proto_parser.h
        proto/comment_parser.c
        proto/comment_parser.h
        proto/syntax_parser.c
        proto/syntax_parser.h
        proto/detector.c
        proto/detector.h
        proto/package_parser.c
        proto/package_parser.h
        proto/option_parser.c
        proto/option_parser.h
        proto/import_parser.c
        proto/import_parser.h
        proto/message_parser.c
        proto/message_parser.h
        proto/message_ele_parser.c
        proto/message_ele_parser.h
        proto/object_parser.c
        proto/object_parser.h
        proto/enum_parser.c
        proto/enum_parser.h
        proto/service_parser.c
        proto/service_parser.h
        proto/extend_parser.c
        proto/extend_parser.h
        proto/oneof_parser.c
        proto/oneof_parser.h
        proto/enum_ele_parser.c
        proto/enum_ele_parser.h
        proto/service_ele_parser.c
        proto/service_ele_parser.h
        lib/linked_list.c
        lib/linked_list.h
        lib/dir.c
        lib/dir.h
        lib/stack.c
        lib/stack.h
        lib/doubly_linked_list.c
        lib/doubly_linked_list.h
        lib/queue.c lib/queue.h
        lib/str.c
        lib/str.h
        lib/str_queue.c
        lib/str_queue.h
        lib/g_list.c
        lib/g_list.h
        lib/uuid.c
        lib/uuid.h
        lib/file.c
        lib/file.h
        util/util.c
        util/util.h
        util/file_helper.c
        util/file_helper.h
        lib/memory.c
        lib/memory.h
        lib/type.c
        lib/type.h
        lib/os.c
        lib/os.h
        proto/common.c
        proto/common.h
        json/json_parser.c
        json/json_parser.h)

configure_file(tests/lib/test_data/malformed/test_data_1.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/lib/test_data/malformed/test_data_1.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_1.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_1.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_2.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_2.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_3.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_3.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_4.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_4.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_5.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_5.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_6.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_6.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_7.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_7.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_8.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_8.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_9.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_9.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_10.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_10.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_11.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_11.proto COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_1.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_1.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_2.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_2.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_3.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_3.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_4.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_4.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_5.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_5.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_6.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_6.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_7.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_7.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_8.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_8.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_9.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_9.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_10.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_10.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_11.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_11.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_4.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_new_lines.proto.txt COPYONLY)

add_executable(openfmt-lib-tester
        tests/lib/main.c
        tests/lib/test_str.c
        tests/lib/test_str.h
        tests/lib/g_list_test.c
        tests/lib/g_list_test.h
        tests/lib/test_dir.c
        tests/lib/test_dir.h
        tests/lib/test_uuid.c
        tests/lib/test_uuid.h
        tests/lib/test_g_hash_table.c
        tests/lib/test_g_hash_table.h
        tests/macro.c
        tests/macro.h
        lib/dir.c
        lib/dir.h
        lib/str.c
        lib/str.h
        lib/linked_list.c
        lib/linked_list.h
        lib/uuid.c
        lib/uuid.h
        lib/g_hash_table.c
        lib/g_hash_table.h
        lib/memory.c
        lib/memory.h
        lib/type.c
        lib/type.h
        lib/os.c
        lib/os.h)

add_executable(openfmt-tester
        tests/proto/main.c
        tests/proto/test_file_format.c
        tests/proto/test_file_format.h
        tests/macro.c
        tests/macro.h
        proto/proto.c
        proto/proto.h
        proto/proto_parser.c
        proto/proto_parser.h
        proto/comment_parser.c
        proto/comment_parser.h
        proto/syntax_parser.c
        proto/syntax_parser.h
        proto/detector.c
        proto/detector.h
        proto/package_parser.c
        proto/package_parser.h
        proto/option_parser.c
        proto/option_parser.h
        proto/import_parser.c
        proto/import_parser.h
        proto/message_parser.c
        proto/message_parser.h
        proto/message_ele_parser.c
        proto/message_ele_parser.h
        proto/object_parser.c
        proto/object_parser.h
        proto/enum_parser.c
        proto/enum_parser.h
        proto/service_parser.c
        proto/service_parser.h
        proto/extend_parser.c
        proto/extend_parser.h
        proto/oneof_parser.c
        proto/oneof_parser.h
        proto/enum_ele_parser.c
        proto/enum_ele_parser.h
        proto/service_ele_parser.c
        proto/service_ele_parser.h
        lib/linked_list.c
        lib/linked_list.h
        lib/dir.c
        lib/dir.h
        lib/stack.c
        lib/stack.h
        lib/doubly_linked_list.c
        lib/doubly_linked_list.h
        lib/queue.c lib/queue.h
        lib/str.c
        lib/str.h
        lib/str_queue.c
        lib/str_queue.h
        lib/g_list.c
        lib/g_list.h
        lib/uuid.c
        lib/uuid.h
        lib/file.c
        lib/file.h
        util/util.c
        util/util.h
        util/file_helper.c
        util/file_helper.h
        lib/memory.c
        lib/memory.h
        lib/type.c
        lib/type.h
        lib/os.c
        lib/os.h
        proto/common.c
        proto/common.h
        json/json_parser.c
        json/json_parser.h)

enable_testing()
add_subdirectory(tests/lib)
add_subdirectory(tests/proto)
