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
#include "common/basic_shader_program.h"
#include "common/path.h"
#include "common/shader.h"

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
    glClearBufferfv(GL_COLOR, 0, background.data());
    draw_triangle(current_time);
    check_error();
  }

  void start_up() override {
    Shader vertex(get_full_path("ch03/vert.vert"), GL_VERTEX_SHADER);
    Shader frag(get_full_path("ch03/frag.frag"), GL_FRAGMENT_SHADER);
    Shader tesc(get_full_path("ch03/tesselation.tesc"), GL_TESS_CONTROL_SHADER);
    Shader tese(get_full_path("ch03/tesselation.tese"),
                GL_TESS_EVALUATION_SHADER);
    Shader gs(get_full_path("ch03/geometry.gs"), GL_GEOMETRY_SHADER);

    program_ = std::make_unique<BasicProgram>();
    program_->AddShader(vertex.Get());
    // program_->AddShader(tesc.Get());
    // program_->AddShader(tese.Get());
    // program_->AddShader(gs.Get());
    program_->AddShader(frag.Get());
    program_->Link();

    if (glCreateVertexArrays) {
      glCreateVertexArrays(1, &vao_);
    } else {
      glGenVertexArrays(1, &vao_);
    }
    glBindVertexArray(vao_);

    glPointSize(5);
  }

  void shut_down() override { glDeleteVertexArrays(1, &vao_); }

  void draw_triangle(const double current_time) {
    glUseProgram(program_->Get());
    std::array<GLfloat, 4> attribute = {0, 0.5, 0.5f, 0.0f};
    glVertexAttrib4fv(0, attribute.data());
    glVertexAttrib4fv(1, attribute.data());

    // glPatchParameteri(GL_PATCH_VERTICES, 3);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    check_error();
  }

private:
  std::unique_ptr<BasicProgram> program_;
  GLuint vao_ = 0;
  std::array<GLfloat, 4> background{0.99f, 0.96f, 0.90f, 1.0f};
};