#include "common/path.h"
#include "common/utility.h"
#include "tinyply.h"

#include <array>
#include <fstream>
#include <iostream>
#include <memory>

using namespace tinyply;

using float3 = std::array<float, 3>;
using double3 = std::array<double, 3>;

void read_ply_file(const std::string &file_path) {
  println("Now Reading: {}", file_path);

  try {
    std::ifstream file_stream(file_path, std::ios::binary);

    if (file_stream.fail()) {
      throw std::runtime_error("file_stream failed to open " + file_path);
    }

    PlyFile file;
    file.parse_header(file_stream);
    for (const auto &elem : file.get_elements()) {
      println("element name:{}", elem.name);
    }
    std::shared_ptr<PlyData> vertices, faces;

    // The header information can be used to programmatically extract properties
    // on elements known to exist in the header prior to reading the data. For
    // brevity of this sample, properties like vertex position are hard-coded:
    try {
      vertices =
          file.request_properties_from_element("vertex", {"x", "y", "z"});
    } catch (const std::exception &e) {
      println_error("Caught tinyply exception: {}", e.what());
    }

    // Providing a list size hint (the last argument) is a 2x performance
    // improvement. If you have arbitrary ply files, it is best to leave this 0.
    try {
      faces =
          file.request_properties_from_element("face", {"vertex_indices"}, 3);
    } catch (const std::exception &e) {
      std::cerr << "tinyply exception: " << e.what() << std::endl;
    }

    if (vertices) {
      println("Read {} verteices", faces->count);
    }

    if (faces) {
      println("Read {} faces(triangles)", faces->count);
    }
    file.read(file_stream);

    // Example One: converting to your own application types
    {
      const size_t numVerticesBytes = vertices->buffer.size_bytes();
      std::vector<float3> verts(vertices->count);
      std::memcpy(verts.data()->data(), vertices->buffer.get(),
                  numVerticesBytes);
      println("vertices size is {}", verts.size());
    }

  } catch (const std::exception &e) {
    println_error("Caught tinyply exception: {}", e.what());
  }
}

int main(int argc, char *argv[]) {
  read_ply_file(get_full_path("data/bunny.ply"));

  return 0;
}