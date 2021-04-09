cmake_minimum_required(VERSION 3.16)
project(Lesson7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

message(STATUS "OpenGL:")
message(STATUS "    include dirs: ${OPENGL_INCLUDE_DIRS}")
message(STATUS "    libraries   : ${OPENGL_LIBRARIES}")
message(STATUS "GLUT:")
message(STATUS "    include dirs: ${GLUT_INCLUDE_DIR}")
message(STATUS "    libraries   : ${GLUT_LIBRARY}")
message(STATUS "glfw3:")
message(STATUS "    include dirs: ${GLFW3_INCLUDE_DIR}")
message(STATUS "    libraries   : ${GLFW3_LIBRARIES}")
message(STATUS "GLEW:")
message(STATUS "    include dirs: ${GLEW_INCLUDE_DIRS}")
message(STATUS "    libraries   : ${GLEW_LIBRARIES}")

set(root ${CMAKE_SOURCE_DIR})

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}

    ${root}/
    ${root}/deps/dep_imgui
    ${root}/deps/dep_stb

    ${root}/core
    ${root}/core/window
    ${root}/core/shader
    ${root}/core/mash
    ${root}/core/mash/templates
    ${root}/core/texture
    ${root}/core/logger
)

set(sources
    ${root}/core/main.cpp
    ${root}/core/window/window.cpp
    ${root}/core/shader/shader.cpp
    ${root}/core/mash/mash.cpp
    ${root}/core/mash/vertex.cpp
    ${root}/core/mash/templates/templates.cpp
    ${root}/core/texture/texture.cpp
    ${root}/core/texture/texturegen.cpp
    ${root}/core/logger/logger.cpp
)
set(includes
    ${root}/core/incs.hpp
    ${root}/core/window/window.hpp
    ${root}/core/shader/shader.hpp
    ${root}/core/mash/mash.hpp
    ${root}/core/mash/vertex.hpp
    ${root}/core/mash/templates/templates.hpp
    ${root}/core/texture/texture.hpp
    ${root}/core/texture/texturegen.hpp
    ${root}/core/logger/logger.hpp
)

add_subdirectory(${root}/deps/dep_imgui)
add_subdirectory(${root}/deps/dep_stb)

add_executable(${PROJECT_NAME} ${sources} ${includes})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} stbimg)
