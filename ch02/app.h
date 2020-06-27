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

#include <array>

class App : public Application {
    public:
    void render(double current_time) {
        static const std::array<GLfloat,4> red{1.0, 0.0,0.0, 1.0};
        glClearBufferfv(GL_COLOR,0, red.data());
    }
};