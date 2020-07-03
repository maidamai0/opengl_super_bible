#pragma once

/**
 * @file program.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   simple shader program with vertex and fragment shaders
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
#include "common/basic_shader_program.h"
#include "common/shader.h"

#include <memory>
#include <string>

class Program : public BasicProgram {
public:
  Program(std::string &&vertex, std::string &&fragment)
      : vertex_shader_(
            std::make_unique<Shader>(std::move(vertex), GL_VERTEX_SHADER)),
        fragment_shader_(
            std::make_unique<Shader>(std::move(fragment), GL_FRAGMENT_SHADER)) {
    AddShader(vertex_shader_->Get());
    AddShader(fragment_shader_->Get());
    Link();
  }

  ~Program() override = default;

private:
  std::unique_ptr<Shader> vertex_shader_;
  std::unique_ptr<Shader> fragment_shader_;
};