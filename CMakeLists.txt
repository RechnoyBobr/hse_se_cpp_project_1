cmake_minimum_required(VERSION 3.28)
project(project_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_1 main.cxx)

add_subdirectory(lib)

target_link_libraries(project_1 PUBLIC lInt)

target_include_directories(project_1 PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/lib"
)