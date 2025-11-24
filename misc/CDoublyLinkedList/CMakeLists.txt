cmake_minimum_required(VERSION 3.26)
project(CDoublyLinkedList C)

set(CMAKE_C_STANDARD 23)

# unit testing framework
include(FetchContent)
FetchContent_Declare(
        Tau
        URL https://github.com/jasmcaus/tau/archive/dev.zip
)
FetchContent_MakeAvailable(Tau)

add_library(CDoublyLinkedList library.c)

enable_testing()

add_executable(
        UnitTests
        test_list.c
)

target_link_libraries(
        UnitTests
        Tau
)
