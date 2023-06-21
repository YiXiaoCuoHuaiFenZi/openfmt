cmake_minimum_required(VERSION 3.23)
project(openfmt-tester)

set(CMAKE_C_STANDARD 99)

enable_testing()

# test for format proto files under a directory.
add_test(NAME test_format_directory COMMAND openfmt-tester test_format_directory)
