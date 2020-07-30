#include "common/app.h"
#include "common/path.h"
#include "common/program.h"
#include "common/utility.h"
#include "glm/vec4.hpp"

#include <memory>

// attributes
static const std::array<GLfloat, 12> position = {
    0.25, -0.25, 0.5, 1.0, -0.25, -0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};
static const std::array<GLfloat, 12> color = {
    0.25, 0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};

class APP522 : public Application {
public:
  APP522() = default;
  ~APP522() = default;

protected:
  void render(double current_time) override { draw_triangle(); }
  void start_up() override {
    // vao
    glCreateVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // shader program
    program_ = std::make_unique<Program>(get_full_path("ch05/vert_522.vert"),
                                         get_full_path("ch05/frag_522.frag"));

    // vbo
    glCreateBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glNamedBufferStorage(vbo_, byte_size(position), position.data(),
                         GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayVertexBuffer(vao_, 0, vbo_, 0, sizeof(glm::vec4));
    glVertexArrayAttribFormat(vao_, 0, sizeof(glm::vec4), GL_FLOAT, GL_FALSE,
                              0);
    glEnableVertexArrayAttrib(vao_, 0);
  }
  void shut_down() override {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
  }

private:
  void draw_triangle() {
    glUseProgram(program_->Get());
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  std::unique_ptr<Program> program_;
  GLuint vao_ = 0;
  GLuint vbo_ = 0;
};

auto main(int argc, char **argv) -> int {
  APP522 app;
  app.Run();
}