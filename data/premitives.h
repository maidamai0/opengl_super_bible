#pragma once

/**
 * @file premitives.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   some common premitives such as triangle,cube
 * @version 0.1
 * @date 2020-08-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "glad/glad.h"
#include <array>

// clang-format off
inline const std::array<GLfloat, 12> triangle = {
    0.25,  -0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
    0.25,   0.25, 0.5, 1.0};

inline const std::array<GLfloat, 12> triangle_color = {
    0.25, 0.25, 0.5, 1.0,
    0.25, 0.25, 0.5, 1.0,
    0.25, 0.25, 0.5, 1.0};

// inline const std::array<GLfloat, 36> cube = {
//     -0.25f, 0.25f,  -0.25f,
//     -0.25f, -0.25f, -0.25f,
//      0.25f, -0.25f, -0.25f,

//      0.25f, -0.25f, -0.25f, 
//      0.25f,  0.25f, -0.25f, 
//     -0.25f,  0.25f, -0.25f,
 
//     -0.25f,  0.25f, -0.25f,
//      0.25f,  0.25f, -0.25f, 
//      0.25f,  0.25f,  0.25f,
     
//      0.25f,  0.25f,  0.25f,
//     -0.25f,  0.25f,  0.25f,
//     -0.25f,  0.25f, -0.25f,
// };

inline const std::array<GLfloat, 36*3> cube = {
    // bottom plane, all z are negative
    -0.25f,  0.25f, -0.25f,
    -0.25f, -0.25f, -0.25f,
     0.25f, -0.25f, -0.25f,

     0.25f, -0.25f, -0.25f, 
     0.25f,  0.25f, -0.25f, 
    -0.25f,  0.25f, -0.25f,

    // top plane, all z are positive
    -0.25f,  0.25f,  0.25f,
    -0.25f, -0.25f,  0.25f,
     0.25f, -0.25f,  0.25f,

     0.25f, -0.25f,  0.25f, 
     0.25f,  0.25f,  0.25f, 
    -0.25f,  0.25f,  0.25f,
 
    // right plane,all y are positive
    -0.25f,  0.25f, -0.25f,
     0.25f,  0.25f, -0.25f, 
     0.25f,  0.25f,  0.25f,
     
     0.25f,  0.25f,  0.25f,
    -0.25f,  0.25f,  0.25f,
    -0.25f,  0.25f, -0.25f,

    // left plane,all y are negative
    -0.25f,  -0.25f, -0.25f,
     0.25f,  -0.25f, -0.25f, 
     0.25f,  -0.25f,  0.25f,
     
     0.25f,  -0.25f,  0.25f,
    -0.25f,  -0.25f,  0.25f,
    -0.25f,  -0.25f, -0.25f,

    // front plane, all x are positive
     0.25f,  -0.25f, -0.25f,
     0.25f,   0.25f, -0.25f, 
     0.25f,   0.25f,  0.25f,
     
     0.25f,   0.25f,  0.25f,
     0.25f,  -0.25f,  0.25f,
     0.25f,  -0.25f, -0.25f,

    // back plane, all x are negative
    -0.25f,  -0.25f, -0.25f,
    -0.25f,   0.25f, -0.25f, 
    -0.25f,   0.25f,  0.25f,
     
    -0.25f,   0.25f,  0.25f,
    -0.25f,  -0.25f,  0.25f,
    -0.25f,  -0.25f, -0.25f,
};
// clang-format on