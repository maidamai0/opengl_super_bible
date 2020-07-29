#pragma once

/**
 * @file ply_reader.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   read ply files
 * @version 0.1
 * @date 2020-07-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "common/path.h"
#include "common/utility.h"
#include "tinyply.h"

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vcruntime_string.h>
#include <vector>

class pLYReader {
public:
  using DataPtr = std::shared_ptr<tinyply::PlyData>;

  pLYReader(const std::string &file_path) { read_ply_file(file_path); }

  std::vector<std::array<float, 3>> GetVertices() {
    std::vector<std::array<float, 3>> ret(vertices_->count);
    memcpy(ret.data(), vertices_->buffer.get(), vertices_->buffer.size_bytes());
    return ret;
  }

private:
  void read_ply_file(const std::string &file_path) {
    std::ifstream file_stream(file_path, std::ios::binary);

    if (file_stream.fail()) {
      throw std::runtime_error("file_stream failed to open " + file_path);
    }

    ply_file_.parse_header(file_stream);
    request_vertices();
    request_faces();
    ply_file_.read(file_stream);
  }

  auto request_vertices() -> void {
    vertices_ =
        ply_file_.request_properties_from_element("vertex", {"x", "y", "z"});
  }

  auto request_faces() -> void {
    _faces_ = ply_file_.request_properties_from_element("face",
                                                        {"vertex_indices"}, 3);
  }

private:
  tinyply::PlyFile ply_file_;
  DataPtr vertices_;
  DataPtr _faces_;
};