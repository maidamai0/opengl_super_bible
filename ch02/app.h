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

#include "cmath"
#include <array>
#include <chrono>
#include <thread>

class App : public Application {
public:
  void render(double current_time) {
    const auto r = sin(static_cast<float>(current_time)) / 2 + 0.5f;
    const auto g = sin(static_cast<float>(current_time) + 1.0f / 3) / 2 + 0.5f;
    const auto b = sin(static_cast<float>(current_time) + 2.0f / 3) / 2 + 0.5f;
    const std::array<GLfloat, 4> red{r, g, b, 0.1f};
    glClearBufferfv(GL_COLOR, 0, red.data());
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
};