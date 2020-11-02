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

file(GLOB_RECURSE SRCS_TEST "app/tests/*.cpp")
file(GLOB_RECURSE SRCS_SERVER "app/src/server/*.cpp")
file(GLOB_RECURSE SRCS_CLIENT "app/src/client/*.cpp")
file(GLOB_RECURSE SRCS_LIBS "app/lib/*.cpp")

file(GLOB_RECURSE SRCS_SERVER_CLASS "app/src/server/Class/*.cpp")

include_directories(${CMAKE_INCLUDE_PATH} "app/include")

add_executable(r-type_server ${SRCS_SERVER} ${SRCS_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})

add_executable(r-type_client ${SRCS_CLIENT} ${SRCS_LIBS})
target_link_libraries(r-type_client ${CONAN_LIBS})

add_executable(r-type_tests ${SRCS_TEST} ${SRCS_LIBS} ${SRCS_SERVER_CLASS})
target_link_libraries(r-type_tests ${CONAN_LIBS})