#pragma once

/**
 * @file utility.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   common things not related to other catagory
 * @version 0.1
 * @date 2020-07-21
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "fmt/format.h"

template <typename T> constexpr void unused(T &&) {}

/**
 * @brief Wrapper of fmt::print
 *
 * @tparam S
 * @tparam Args
 * @tparam char_t<S>
 * @param format_str
 * @param args
 */
template <typename S, typename... Args, typename Char = fmt::char_t<S>>
inline void println(const S &format_str, Args &&... args) {
  fmt::print(format_str, args...);
  std::fflush(stdout);
}