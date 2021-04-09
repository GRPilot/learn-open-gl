cmake_minimum_required(VERSION 3.1)

project(Lesson4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    main.cpp
    glad/glad.c
)
set(HEADERS
    platform.h
    glad/glad.h
    glad/khrplatform.h
)

set(INC_DIRS
    ${PROJECT_SOURCE_DIR}/window/
    ${PROJECT_SOURCE_DIR}/shader/
    ${PROJECT_SOURCE_DIR}/vertex/
)

set(LINKING_SUBPROJECTS "")

foreach(DIR ${INC_DIRS})
    message(STATUS "Add subdirectory:\n\t${DIR}")
    include_directories(${DIR})
    add_subdirectory(${DIR})
    get_directory_property(LINKING_SUBPROJECTS DIRECTORY ${DIR} DEFINITION LINKING_SUBPROJECTS)
endforeach()

set(DEPS -lGL -lGLEW -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${DEPS})
target_link_libraries(${PROJECT_NAME} ${LINKING_SUBPROJECTS})
# target_link_libraries(${PROJECT_NAME} wnd shdr vtx)
