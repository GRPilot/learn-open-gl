cmake_minimum_required(VERSION 3.1)

project(vtx)
message("--------------------- ${PROJECT_NAME} ---------------------")

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h *.hpp)

message(STATUS "Sourcies:\n\t${SOURCES}")
message(STATUS "Headers:\n\t${HEADERS}")

include_directories(..)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
list(APPEND LINKING_SUBPROJECTS ${PROJECT_NAME})

message("------------------------------------------------")
