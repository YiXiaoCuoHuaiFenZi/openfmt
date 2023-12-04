cmake_minimum_required(VERSION 3.23)
project(openfmt C)

set(CMAKE_C_STANDARD 99)

add_executable(openfmt
        main.c
        proto.c
        proto.h
        proto_parser.c
        proto_parser.h
        comment_parser.c
        comment_parser.h
        syntax_parser.c
        syntax_parser.h
        detector.c
        detector.h
        package_parser.c
        package_parser.h
        option_parser.c
        option_parser.h
        import_parser.c
        import_parser.h
        message_parser.c
        message_parser.h
        message_ele_parser.c
        message_ele_parser.h
        object_parser.c
        object_parser.h
        enum_parser.c
        enum_parser.h
        service_parser.c
        service_parser.h
        extend_parser.c
        extend_parser.h
        oneof_parser.c
        oneof_parser.h
        enum_ele_parser.c
        enum_ele_parser.h
        service_ele_parser.c
        service_ele_parser.h
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
        lib/g_hash_table.c
        lib/g_hash_table.h
        lib/uuid.c
        lib/uuid.h
        lib/hash_table.c
        lib/hash_table.h
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
        lib/os.h)

configure_file(tests/lib/test_data/malformed/test_data_1.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/lib/test_data/malformed/test_data_1.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_1.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_1.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_2.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_2.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_3.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_data_3.proto COPYONLY)

configure_file(tests/proto/test_data/malformed/test_data_4.proto ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/malformed/test_new_lines.proto COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_1.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_1.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_2.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_2.proto.txt COPYONLY)

configure_file(tests/proto/test_data/formatted/test_data_3.proto.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/proto/test_data/formatted/test_data_3.proto.txt COPYONLY)

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
        tests/lib/test_hash_table.c
        tests/lib/test_hash_table.h
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
        lib/hash_table.c
        lib/hash_table.h
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
        proto.c
        proto.h
        proto_parser.c
        proto_parser.h
        comment_parser.c
        comment_parser.h
        syntax_parser.c
        syntax_parser.h
        detector.c
        detector.h
        package_parser.c
        package_parser.h
        option_parser.c
        option_parser.h
        import_parser.c
        import_parser.h
        message_parser.c
        message_parser.h
        message_ele_parser.c
        message_ele_parser.h
        object_parser.c
        object_parser.h
        enum_parser.c
        enum_parser.h
        service_parser.c
        service_parser.h
        extend_parser.c
        extend_parser.h
        oneof_parser.c
        oneof_parser.h
        enum_ele_parser.c
        enum_ele_parser.h
        service_ele_parser.c
        service_ele_parser.h
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
        lib/g_hash_table.c
        lib/g_hash_table.h
        lib/uuid.c
        lib/uuid.h
        lib/hash_table.c
        lib/hash_table.h
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
        lib/os.h)

enable_testing()
add_subdirectory(tests/lib)
add_subdirectory(tests/proto)
