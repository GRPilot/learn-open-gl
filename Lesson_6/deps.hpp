#ifndef LESSON_6_TEXTURES_DEPS_HPP
#define LESSON_6_TEXTURES_DEPS_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <random>
#include <memory>

#define INIT_GLFW3 \
    glfwInit(); \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); \
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)

#define INIT_GLAD gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)

using Position3f = glm::vec3;
using Position2f = glm::vec2;
using Size3f = glm::vec3;
using Size2f = glm::vec2;
using Color = glm::vec4;

#endif //LESSON_6_TEXTURES_DEPS_HPP
