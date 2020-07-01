#pragma once

/**
 * @file app.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief First app
 * @version 0.1
 * @date 2020-06-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "common/app.h"
#include "common/path.h"
#include "common/shader.h"

#include "cmath"
#include "memory"
#include <array>
#include <chrono>
#include <thread>

class App final: public Application {
public:
  App() = default;
  ~App() = default;

private:
  void render(double current_time) override {
    const auto r = sin(static_cast<float>(current_time)) / 2 + 0.5f;
    const auto g = sin(static_cast<float>(current_time) + 1.0f / 3) / 2 + 0.5f;
    const auto b = sin(static_cast<float>(current_time) + 2.0f / 3) / 2 + 0.5f;
    const std::array<GLfloat, 4> red{r, g, b, 0.1f};
    glClearBufferfv(GL_COLOR, 0, red.data());

    draw_point();
    check_error();

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  void start_up() override {
    shader_program_ = std::make_unique<Shader>(get_full_path("ch02/vert.vert"),
                                               get_full_path("ch02/frag.frag"));

    glCreateVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
  }

  void shut_down() override { glDeleteVertexArrays(1, &vao_); }

  void draw_point() {
    glUseProgram(shader_program_->Get());
    glPointSize(10.0);
    glDrawArrays(GL_POINTS, 0, 3);
  }

  void draw_triangle() {
    glUseProgram(shader_program_->Get());
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  std::unique_ptr<Shader> shader_program_;
  GLuint vao_ = 0;
};