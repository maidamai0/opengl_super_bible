#include "common/app.h"
#include "common/path.h"
#include "common/program.h"
#include "common/utility.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cmath>
#include <memory>

// attributes
static const std::array<GLfloat, 12> position = {
    0.25, -0.25, 0.5, 1.0, -0.25, -0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};

constexpr auto model_view_location = 1;
constexpr auto perspective_location = 2;

class APP522 : public Application {
public:
  APP522() = default;
  ~APP522() = default;

protected:
  void render(double current_time) override {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_triangle();
  }
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
    glVertexArrayAttribFormat(vao_, 0, 4, GL_FLOAT, GL_TRUE, 0);
    glEnableVertexArrayAttrib(vao_, 0);
  }

  void shut_down() override {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
  }

private:
  void draw_triangle() {
    glUseProgram(program_->Get());
    calculate_projection_matrix();
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE,
                       glm::value_ptr(model_view_));
    glUniformMatrix4fv(perspective_location, 1, GL_FALSE,
                       glm::value_ptr(get_perspective()));

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  auto calculate_projection_matrix() -> void {
    const float time = glfwGetTime() * math_pi * 0.0001;
    model_view_ =
        glm::rotate(model_view_, time * 81.0f, glm::vec3(1.0, 0.0, 0.0));
    model_view_ =
        glm::rotate(model_view_, time * 45.0f, glm::vec3(0.0, 1.0, 0.0));
    // model_view_ = glm::translate(model_view_, glm::vec3(0.0, 0.0, -4.0));
    // model_view_ = glm::translate(
    //     model_view_,
    //     glm::vec3(sinf(2.1f * time) * 0.5f, cosf(1.7f * time) * 0.5f,
    //               sinf(1.3f * time) * cosf(1.5f * time) * 2.0f));
  }

private:
  std::unique_ptr<Program> program_;
  GLuint vao_ = 0;
  GLuint vbo_ = 0;
  glm::mat4 model_view_{1.0f};
};

auto main(int argc, char **argv) -> int {
  APP522 app;
  app.Run();
}