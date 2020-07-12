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

## Code style

All code is formated by [clang-format](https://clang.llvm.org/docs/ClangFormat.html) with default google style.
