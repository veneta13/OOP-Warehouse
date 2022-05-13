cmake_minimum_required(VERSION 3.0.0)
project(stack VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(tests
        tests/test.cpp
        source/container.cpp
        source/shelf.cpp
        source/section.cpp
        source/warehouse.cpp
        source/date.cpp
        source/product.cpp
        source/dyn_array.cpp
        source/tracker.cpp
        source/date_indexer.cpp
        source/file_manager.cpp
        source/executor.cpp)
add_executable(main
        source/main.cpp
        source/container.cpp
        source/shelf.cpp
        source/section.cpp
        source/warehouse.cpp
        source/date.cpp
        source/product.cpp
        source/dyn_array.cpp
        source/tracker.cpp
        source/date_indexer.cpp
        source/file_manager.cpp
        source/executor.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
