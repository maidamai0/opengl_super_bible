#include "common/app.h"
#include "common/path.h"
#include "common/program.h"
#include "common/utility.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

#include <array>
#include <memory>

// attributes
static const std::array<GLfloat, 12> position = {
    0.25, -0.25, 0.5, 1.0, -0.25, -0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};
static const std::array<GLfloat, 12> color = {
    0.25, -0.25, 0.5, 1.0, -0.25, -0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};

class Ch501 : public Application {
private:
  void start_up() override {
    std::array<GLuint, 2> vbo;
    glCreateBuffers(2, &vbo[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    const auto copy_with_map = [&](GLuint buffer, ) {
      auto *ptr = glMapNamedBuffer(vbo[0], GL_WRITE_ONLY);
      memcpy(ptr, position.data(), position.size());
      glUnmapNamedBuffer(vbo[0]);
    };

    const auto copy_directly = [&]() {
      glNamedBufferStorage(vbo[0], position.size(), position.data(),
                           GL_DYNAMIC_STORAGE_BIT);
    };

    // initialize buffer
    glNamedBufferStorage(vbo[0], position.size(), position.data(),
                         GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(vbo[1], color.size(), color.data(),
                         GL_DYNAMIC_STORAGE_BIT);

    unused(copy_with_map);
    unused(copy_directly);

    // create and bind a vao
    glCreateVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // setup vertex attribute
    glVertexArrayVertexBuffer(vao_, 0, vbo[0], 0, sizeof(glm::vec4));
    glVertexArrayAttribFormat(vao_, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao_, 0, 0);
    glEnableVertexAttribArray(0);

    glVertexArrayVertexBuffer(vao_, 0, vbo[1], 0, sizeof(glm::vec3));
    glVertexArrayAttribFormat(vao_, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao_, 1, 1);
    glEnableVertexAttribArray(1);

    shader_program_ = std::make_unique<Program>(
        get_full_path("ch05/vert.vetx"), get_full_path("ch05/frag.grag"));
  }

  void render(double current_time) override { draw_triangle(); }
  void shut_down() override { glDeleteVertexArrays(vao_); }

  void draw_triangle() {
    glUseProgram(shader_program_->Get());
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  std::unique_ptr<Program> shader_program_;
  GLuint vao_ = 0;
};

auto main(int argc, char **argv) -> int {
  Ch501 app;
  app.Run();

  return 0;
}