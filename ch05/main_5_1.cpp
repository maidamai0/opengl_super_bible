#include "common/app.h"

#include <array>
#include <vcruntime_string.h>

static const std::array<GLfloat, 12> data = {
    0.25, -0.25, 0.5, 1.0, -0.25, -0.25, 0.5, 1.0, 0.25, 0.25, 0.5, 1.0};

class Ch501 : public Application {
protected:
  void start_up() override {
    GLuint vertex_buffer = 0;
    glCreateBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    const auto copy_with_map = [&]() {
      auto *ptr = glMapNamedBuffer(vertex_buffer, GL_WRITE_ONLY);
      memcpy(ptr, data.data(), data.size());
      glUnmapNamedBuffer(vertex_buffer);
    };

    const auto copy_directly = [&]() {
      glNamedBufferStorage(vertex_buffer, data.size(), data.data(),
                           GL_DYNAMIC_STORAGE_BIT);
    };
  }
  void render(double current_time) override {}
  void shut_down() override {}
};