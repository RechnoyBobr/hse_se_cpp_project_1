cmake_minimum_required(VERSION 3.27)
project(project_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_1 main.cxx test_1.cc)

add_subdirectory(lib)

target_link_libraries(project_1 PUBLIC bigF GTest::gtest_main)
target_include_directories(project_1 PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/lib"
)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)
gtest_discover_tests(project_1)
