#pragma once

/**
 * @file shader.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief  opengl shader class
 * @version 0.1
 * @date 2020-07-03
 *
 * @copyright Copyright (c) 2020
 *
 */

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

class Shader {
public:
  Shader(std::string &&source_path, GLenum type) {
    compile_shaders(source_path, type);
  }

  ~Shader() { glDeleteShader(shader_); };

  GLuint Get() const { return shader_; }

private:
  auto read_shader_source(std::string path) -> std::string {
    std::ifstream file(path);
    if (!file.is_open()) {
      assert(false && "file not found");
    }
    std::stringstream ss;
    while (file >> ss.rdbuf()) {
    };
    return ss.str();
  }

  void compile_shaders(const std::string &source_path, const GLenum type) {
    shader_ = glCreateShader(type);
    source_ = read_shader_source(source_path);
    auto temp = source_.c_str();
    glShaderSource(shader_, 1, &(temp), nullptr);
    glCompileShader(shader_);
    if (!check_shader_compile(shader_)) {
      return;
    }
  }

  bool check_shader_compile(GLint shader) {
    GLint succeed = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succeed);
    if (succeed == GL_FALSE) {
      GLint max_length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
      std::vector<GLchar> error(max_length);
      glGetShaderInfoLog(shader, max_length, &max_length, error.data());

      std::cerr << "Compile shader error: " << error.data();
      assert(false && "invalid shader");

      glDeleteShader(shader);
      return false;
    }

    return true;
  }

private:
  std::string source_;
  GLuint shader_ = 0;
};