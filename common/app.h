#pragma once

/**
 * @file app.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   app base class serveed as a framework, implement sb7.h
 * @version 0.1
 * @date 2020-06-27
 *
 * @copyright Copyright (c) 2020
 *
 */

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include <iostream>
#include <string>
#include <functional>

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

  virtual void run() {
    if (glfwInit() != GL_TRUE) {
      std::cerr << "initalize glfw failed" << std::endl;
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
      std::cerr << "Create window error" << std::endl;
      return;
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
      return;
    }

    // Define the viewport dimensions
    glViewport(0, 0, info_.windowWidth, info_.windowHeight);

    glfwSetWindowSizeCallback(window_,&Application::on_resize);
    glfwSetKeyCallback(window_, &Application::on_key);
    glfwSetMouseButtonCallback(window_, &Application::on_mouse_button);
    glfwSetCursorPosCallback(window_, &Application::on_mouse_move);
    glfwSetScrollCallback(window_, &Application::on_mouse_wheel);
    if (!info_.flags.cursor) {
      glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    std::cout << "OpenGL: " << glGetString(GL_VENDOR) << " "
              << glGetString(GL_VERSION) << " " << glGetString(GL_RENDERER)
              << std::endl;

    if (info_.flags.debug) {
      //   glDebugMessageCallback((GLDEBUGPROC)debug_callback, this);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }

    while (glfwWindowShouldClose(window_) != GL_TRUE) {
      render(glfwGetTime());

      glfwSwapBuffers(window_);
      glfwPollEvents();
    }

    glfwDestroyWindow(window_);
    glfwTerminate();
  }

  void load_settings() {
    info_.title = "OpenGL SuperBible Example";
    info_.windowWidth = 800;
    info_.windowHeight = 600;
    info_.majorVersion = 4;
    info_.minorVersion = 6;
    info_.samples = 0;
    info_.flags.all = 0;
    info_.flags.cursor = 1;
  }

protected:
  static void on_resize(GLFWwindow *window, int w, int h) {}

  static void on_key(GLFWwindow *window, int key, int scancode, int action, int mods) {
  }

  static void on_mouse_button(GLFWwindow *window, int button, int action, int mods) {}

  static void on_mouse_move(GLFWwindow *window, double x, double y) {}

  static void on_mouse_wheel(GLFWwindow *window, double xoffset, double yoffset) {}
  static void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                      GLsizei length, const GLchar *message,
                      GLvoid *userParam){};

  virtual void render(double current_time) {}

private:
  AppInfo info_;
  GLFWwindow *window_ = nullptr;
};