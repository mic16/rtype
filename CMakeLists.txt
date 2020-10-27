cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(RType)
add_definitions("-fPIC -lm")

# Append cmake folder to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

message(STATUS "cmake: ${cmake_res}: ${cmake_out}")

file(GLOB_RECURSE SRCS_SERVER "app/src/server/*.cpp")
file(GLOB_RECURSE SRCS_CLIENT "app/src/client/*.cpp")
file(GLOB_RECURSE SRCS_LIBS "lib/*.cpp")

include_directories(${CMAKE_INCLUDE_PATH} "app/include")

add_executable(r-type_server ${SRCS_SERVER} ${SRCS_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})

add_executable(r-type_client ${SRCS_CLIENT} ${SRCS_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS})