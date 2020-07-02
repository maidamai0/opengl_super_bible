/**
 * @brief
 *
 */

#pragma once

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
  Shader(std::string &&vertex, std::string &&fragment) {
    compile_shaders(vertex, fragment);
  }

  ~Shader() { glDeleteShader(program_); }

  GLuint Get() const { return program_; }

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

  void compile_shaders(const std::string &v, const std::string &f) {
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    vertex_source_ = read_shader_source(v);
    auto temp = vertex_source_.c_str();
    glShaderSource(vertex_shader, 1, &(temp), nullptr);
    glCompileShader(vertex_shader);
    if (!check_shader_compile(vertex_shader)) {
      return;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    fragment_source_ = read_shader_source(f);
    temp = fragment_source_.c_str();
    glShaderSource(fragment_shader, 1, &temp, nullptr);
    glCompileShader(fragment_shader);
    if (!check_shader_compile(fragment_shader)) {
      return;
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    glLinkProgram(program_);

    if (!check_program(program_)) {
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);
      return;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
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

  bool check_program(GLuint program) {
    GLint succeed = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &succeed);
    if (succeed == GL_FALSE) {
      GLint max_length = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
      std::vector<GLchar> error(static_cast<size_t>(max_length), 0);
      glGetProgramInfoLog(program, max_length, &max_length, error.data());
      std::cerr << "Link program error: " << error.data() << std::endl;
      assert(false && "invaid shader program");
      glDeleteProgram(program_);
      return false;
    }

    return true;
  }

private:
  std::string vertex_source_;
  std::string fragment_source_;
  GLuint program_ = 0;
};