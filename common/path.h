#pragma once

/**
 * @file path.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief get full path
 * @version 0.1
 * @date 2020-06-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef ROOT_PATH
#define ROOT_PATH ""
#endif

#include <string>

auto get_full_path(std::string &&file) -> std::string {
  return ROOT_PATH + file;
}