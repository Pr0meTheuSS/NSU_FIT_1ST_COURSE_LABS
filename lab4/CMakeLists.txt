cmake_minimum_required(VERSION 3.5.1)
project(lab4 C)

set(SRC src/main.c src/Stack.c src/Token.c src/ReversedPolishNotation.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
