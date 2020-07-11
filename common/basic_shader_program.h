#pragma once

/**
 * @file basic_shadere_program.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief  basic shader program
 * @version 0.1
 * @date 2020-07-03
 *
 * @copyright Copyright (c) 2020
 *
 */

// clang-format off
#include "fmt/core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include <vector>
#include <iostream>
#include <cassert>

class BasicProgram {
public:
  BasicProgram() : program_(glCreateProgram()){};
  virtual ~BasicProgram() { glDeleteShader(program_); }

  void AddShader(GLuint shader) {
    glAttachShader(program_, shader);
    shaders_.push_back(shader);
  }

  GLuint Get() const { return program_; }
  void Link() {
    glLinkProgram(program_);
    for (const auto shader : shaders_) {
      glDeleteShader(shader);
    }

    if (!check_program(program_)) {
      return;
    }
  }

protected:
  bool check_program(GLuint program) {
    GLint succeed = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &succeed);
    if (succeed == GL_FALSE) {
      GLint max_length = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
      std::vector<GLchar> error(static_cast<size_t>(max_length), 0);
      glGetProgramInfoLog(program, max_length, &max_length, error.data());
      fmt::print(stderr, "Link program error: {}\n", error.data());
      assert(false && "invaid shader program");
      glDeleteProgram(program_);
      return false;
    }

    return true;
  }

private:
  GLuint program_ = 0;
  std::vector<GLuint> shaders_;
};