#include "common/ply_reader.h"
#include <iostream>

using namespace tinyply;

using float3 = std::array<float, 3>;
using double3 = std::array<double, 3>;

void read_ply_file(const std::string &file_path) {
  pLYReader reader(file_path);

  println("Now Reading: {}", file_path);

  try {

    const auto vertices = reader.GetVertices();

    println("Read {} verteices", vertices.size());
    for (const auto &vert : vertices) {
      std::cout << vert;
    }

  } catch (const std::exception &e) {
    println_error("Caught tinyply exception: {}", e.what());
  }
}

int main(int argc, char *argv[]) {
  read_ply_file(get_full_path("data/bunny.ply"));

  return 0;
}