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
#include <ostream>
#include <vcruntime.h>

constexpr auto math_pi = 3.1415926;

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
  fmt::print("\n");
  std::fflush(stdout);
}

template <typename S, typename... Args, typename Char = fmt::char_t<S>>
inline void println_error(const S &format_str, Args &&... args) {
  fmt::print(stderr, format_str, args...);
  fmt::print("\n");
  std::fflush(stdout);
}

/**
 * @brief get byte size of std::array
 *
 * @tparam T      value type of array
 * @tparam N      size of array
 * @param arr     array
 * @return auto   byte size
 */
template <typename T, size_t N> auto byte_size(std::array<T, N> arr) {
  return sizeof(T) * arr.size();
}

/**
 * @brief << operator for std::array
 *
 * @tparam T
 * @tparam N
 * @param os
 * @param arr
 * @return std::ostream&
 */
template <typename T, size_t N>
std::ostream &operator<<(std::ostream &os, std::array<T, N> arr) {
  for (const auto &e : arr) {
    os << e << " ";
  }
  os << std::endl;
  return os;
}