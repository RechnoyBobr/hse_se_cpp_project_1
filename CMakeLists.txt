cmake_minimum_required(VERSION 3.27)
project(project_1)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Core.cmake)

as_library()
with_test(project_1 gtest_main)
add_executable(pie_calc Pie/pie.cxx)
target_link_libraries(pie_calc PRIVATE project_1)
set(CMAKE_CXX_FLAGS "-O2 --coverage")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()