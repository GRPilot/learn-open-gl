cmake_minimum_required(VERSION 3.1)

project(Lesson3)

set(SOURCES main.cpp glad/glad.c)
set(HEADERS glad/glad.h glad/khrplatform.h)
set(DEPS -lGL -lGLEW -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${DEPS})
