#pragma once

/**
 * @file app.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   app base class serveed as a framework, implement sb7.h
 * @version 0.1
 * @date 2020-06-27
 *
 * @remark follow google style
 *
 * @copyright Copyright (c) 2020
 *
 */

// clang-format off
#include "fmt/core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "fmt/format.h"
#include "common/utility.h"

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
#include <functional>
#include <array>
#include <thread>
#include <chrono>
#include <cassert>

namespace {
using namespace std::chrono_literals;
constexpr auto fps_60 = 16ms;
} // namespace

class Application {
public:
  struct AppInfo {
    std::string title;
    int windowWidth;
    int windowHeight;
    int majorVersion;
    int minorVersion;
    int samples;
    union {
      struct {
        unsigned int fullscreen : 1;
        unsigned int vsync : 1;
        unsigned int cursor : 1;
        unsigned int stereo : 1;
        unsigned int debug : 1;
        unsigned int robust : 1;
      };
      unsigned int all;
    } flags;
  };

  Application() = default;
  virtual ~Application() = default;

  virtual void Run() {

    glfwSetErrorCallback(&Application::glfw_error_callback);
    if (glfwInit() != GL_TRUE) {
      println("initalize glfw failed");
      return;
    }

    load_settings();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info_.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info_.minorVersion);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    if (info_.flags.robust) {
      glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
    }
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, info_.samples);
    glfwWindowHint(GLFW_STEREO, info_.flags.stereo ? GL_TRUE : GL_FALSE);

    window_ = glfwCreateWindow(
        info_.windowWidth, info_.windowHeight, info_.title.c_str(),
        info_.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!window_) {
      println("Create window error");
      return;
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      println("Failed to initialize OpenGL context");
      return;
    }

    glEnable(GL_MULTISAMPLE);

    // Define the viewport dimensions
    glViewport(0, 0, info_.windowWidth, info_.windowHeight);

    glfwSetWindowSizeCallback(window_, &Application::on_resize);
    glfwSetKeyCallback(window_, &Application::on_key);
    glfwSetMouseButtonCallback(window_, &Application::on_mouse_button);
    glfwSetCursorPosCallback(window_, &Application::on_mouse_move);
    glfwSetScrollCallback(window_, &Application::on_mouse_wheel);
    if (!info_.flags.cursor) {
      glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    println("OPenGL:{} {} {}", glGetString(GL_VENDOR), glGetString(GL_VERSION),
            glGetString(GL_RENDERER));

    if (info_.flags.debug) {
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback((GLDEBUGPROC)debug_callback, this);
    }

    start_up();

    while (glfwWindowShouldClose(window_) != GL_TRUE) {
      render(glfwGetTime());

      std::this_thread::sleep_for(std::chrono::milliseconds(fps_60));
      glfwSwapBuffers(window_);
      glfwPollEvents();
    }

    shut_down();

    glfwDestroyWindow(window_);
    glfwTerminate();
  }

protected:
  void load_settings() {
    info_.title = "OpenGL SuperBible Example";
    info_.windowWidth = 800;
    info_.windowHeight = 600;
    info_.majorVersion = 4;
    info_.minorVersion = 5;
    info_.samples = 4;
    info_.flags.all = 0;
    info_.flags.cursor = 1;
    info_.flags.debug = 1;
  }

  static void glfw_error_callback(int error, const char *description) {
    println("GLFW error: {}", description);
  }

  static void on_resize(GLFWwindow *window, int w, int h) {}

  static void on_key(GLFWwindow *window, int key, int scancode, int action,
                     int mods) {}

  static void on_mouse_button(GLFWwindow *window, int button, int action,
                              int mods) {}

  static void on_mouse_move(GLFWwindow *window, double x, double y) {}

  static void on_mouse_wheel(GLFWwindow *window, double xoffset,
                             double yoffset) {}
  static void debug_callback(GLenum source, GLenum type, GLuint id,
                             GLenum severity, GLsizei length,
                             const GLchar *message, GLvoid *userParam) {
    std::string source_str;
    switch (source) {
    case GL_DEBUG_SOURCE_API:
      source_str = "API";
      break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      source_str = "WINDOW SYSTEM";
      break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      source_str = "SHADER COMPILER";
      break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
      source_str = "THIRD PARTY";
      break;

    case GL_DEBUG_SOURCE_APPLICATION:
      source_str = "APPLICATION";
      break;

    case GL_DEBUG_SOURCE_OTHER:
      source_str = "UNKNOWN";
      break;

    default:
      source_str = "UNKNOWN";
      break;
    }

    std::string type_str;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      type_str = "ERROR";
      break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      type_str = "DEPRECATED BEHAVIOR";
      break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      type_str = "UDEFINED BEHAVIOR";
      break;

    case GL_DEBUG_TYPE_PORTABILITY:
      type_str = "PORTABILITY";
      break;

    case GL_DEBUG_TYPE_PERFORMANCE:
      type_str = "PERFORMANCE";
      break;

    case GL_DEBUG_TYPE_OTHER:
      type_str = "OTHER";
      break;

    case GL_DEBUG_TYPE_MARKER:
      type_str = "MARKER";
      break;

    default:
      type_str = "UNKNOWN";
      break;
    }

    std::string severity_str;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      severity_str = "HIGH";
      break;

    case GL_DEBUG_SEVERITY_MEDIUM:
      severity_str = "MEDIUM";
      break;

    case GL_DEBUG_SEVERITY_LOW:
      severity_str = "LOW";
      break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
      severity_str = "NOTIFICATION";
      break;

    default:
      severity_str = "UNKNOWN";
      break;
    }

    println("{}:{} {}, raised from {},{}", id, type_str, severity_str,
            source_str, message);
  };

  virtual void render(double current_time) {
    println_error("{} not implemented", __FUNCTION__);
  }
  virtual void start_up() {
    println_error("{} not implemented", __FUNCTION__);
  };
  virtual void shut_down() {
    println_error("{} not implemented", __FUNCTION__);
  };

  void variable_color(double current_time) {
    const auto r = sin(static_cast<float>(current_time)) / 2 + 0.5f;
    const auto g = sin(static_cast<float>(current_time) + 1.0f / 3) / 2 + 0.5f;
    const auto b = sin(static_cast<float>(current_time) + 2.0f / 3) / 2 + 0.5f;
    const std::array<GLfloat, 4> color{r, g, b, 0.1f};
    glClearBufferfv(GL_COLOR, 0, color.data());
  }

  /**
   * @brief check opengl error
   *
   */
  void check_error() {
    const auto error = glGetError();

    switch (error) {
    case GL_NO_ERROR: {
      return;
    }
    case GL_INVALID_ENUM: {
      println_error("{}:GL_INVALID_ENUM", GL_INVALID_ENUM);
    }
    case GL_INVALID_VALUE: {
      println_error("{}:GL_INVALID_VALUE", GL_INVALID_VALUE);
    }
    case GL_INVALID_OPERATION: {
      println_error("{}:GL_INVALID_OPERATION", GL_INVALID_OPERATION);
    }
    case GL_INVALID_FRAMEBUFFER_OPERATION: {
      println_error("{}:GL_INVALID_FRAMEBUFFER_OPERATION",
                 GL_INVALID_FRAMEBUFFER_OPERATION);
    }
    case GL_OUT_OF_MEMORY: {
      println_error("{}:GL_OUT_OF_MEMORY", GL_OUT_OF_MEMORY);
    }
    case GL_STACK_UNDERFLOW: {
      println_error("{}:GL_STACK_UNDERFLOW", GL_STACK_UNDERFLOW);
    }
    case GL_STACK_OVERFLOW: {
      println_error("{}:GL_STACK_OVERFLOW", GL_STACK_OVERFLOW);
    }
    }

    // assert(false && "OpenGL error");
  }

private:
  AppInfo info_;
  GLFWwindow *window_ = nullptr;
};