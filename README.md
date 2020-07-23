# Practice code for [opengl super bible](http://www.openglsuperbible.com/)

## Depndencies

* [glad](https://github.com/Dav1dde/glad)

  Load opengl functions, already in [deps/glad](deps/glad).

* [glfw](https://www.glfw.org/)

  Create windows, install by yourself.Install with [vcpkg](https://github.com/microsoft/vcpkg) is recommended on windows:

  ```batch
  vcpkg install glfw3
  ```

* [fmtlib](https://github.com/fmtlib/fmt)

  Replace std::cout,std::cerr, printf,sprintf... You must install it by yourself.Install with [vcpkg](https://github.com/microsoft/vcpkg) is recommended on windows:

  ```batch
  vcpkg install fmt
  ```

* [glm](https://glm.g-truc.net/0.9.9/index.html)

  Opengl math library.You must install it by yourself.Install with [vcpkg](https://github.com/microsoft/vcpkg) is recommended on windows:

  ```batch
  vcpkg install glm
  ```

## Code style

All code is formated by [clang-format](https://clang.llvm.org/docs/ClangFormat.html) with default google style.

## Documentation

See [documentaion](./doc) for detail.

Some [PlantUML](https://plantuml.com/) code is used in documentation and github markdown does't suport it for now. So, I recommend to render these markdow files by yourself with a editor support plantuml embedd with plantuml. VScode with a plantuml extesnion is a good choice.
