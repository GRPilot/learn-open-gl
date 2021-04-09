cmake_minimum_required(VERSION 3.16)
project(Lesson_6_Textures)

set(CMAKE_CXX_STANDARD 11)
set(root ${CMAKE_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 3.3 REQUIRED)

message(STATUS "OpenGL:")
message(STATUS "    include dirs: ${OPENGL_INCLUDE_DIRS}")
message(STATUS "    libraries   : ${OPENGL_LIBRARIES}")
message(STATUS "GLUT:")
message(STATUS "    include dirs: ${GLUT_INCLUDE_DIRS}")
message(STATUS "    libraries   : ${GLUT_LIBRARY}")

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}

    ${root}/
    ${root}/core
    ${root}/core/window
    ${root}/core/random
    ${root}/core/shader
    ${root}/core/texture
    ${root}/core/mash
    ${root}/dependencies
)

set(SOURCES
    ${root}/main.cpp
    ${root}/core/window/window.cpp
    ${root}/core/random/randomgenerator.cpp
    ${root}/core/shader/shader.cpp
    ${root}/core/texture/stb_image.cpp
    ${root}/core/texture/texture.cpp
    ${root}/core/texture/texturegen.cpp
    ${root}/core/mash/vertex.cpp
    ${root}/core/mash/mash.cpp
)

set(INCLUDES
    ${root}/deps.hpp
    ${root}/core/window/window.hpp
    ${root}/core/random/randomgenerator.hpp
    ${root}/core/shader/shader.hpp
    ${root}/core/texture/stb_image.h
    ${root}/core/texture/texture.hpp
    ${root}/core/texture/texturegen.hpp
    ${root}/core/mash/vertex.hpp
    ${root}/core/mash/mash.hpp
)

add_subdirectory(dependencies)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARY})
target_link_libraries(${PROJECT_NAME} glfw glad)
