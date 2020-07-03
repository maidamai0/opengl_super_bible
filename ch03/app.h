#pragma once
/**
 * @file app.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief app for ch03
 * @version 0.1
 * @date 2020-07-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "common/app.h"
#include "common/path.h"
#include "common/program.h"

#include <array>
#include <cmath>
#include <memory>
#include <string>

class App03 final : public Application {
public:
  App03() = default;
  ~App03() = default;

private:
  void render(double current_time) override {
    variable_color(current_time);
    draw_triangle(current_time);
    check_error();
  }

  void start_up() override {
    shader_ = std::make_unique<Program>(get_full_path("ch03/vert.vert"),
                                       get_full_path("ch03/frag.frag"));

    if (glCreateVertexArrays) {
      glCreateVertexArrays(1, &vao_);
    } else {
      glGenVertexArrays(1, &vao_);
    }
    glBindVertexArray(vao_);
  }

  void shut_down() override { glDeleteVertexArrays(1, &vao_); }

  void draw_triangle(const double current_time) {
    glUseProgram(shader_->Get());
    std::array<GLfloat, 4> attribute = {static_cast<GLfloat>(sin(current_time)*0.5f),
                                        static_cast<GLfloat>(cos(current_time)*0.5f),
                                        0.0f, 0.0f};
    glVertexAttrib4fv(0, attribute.data());
    glVertexAttrib4fv(1, attribute.data());

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  std::unique_ptr<Program> shader_;
  GLuint vao_ = 0;
};