# Practice code for [opengl super bible](http://www.openglsuperbible.com/)

## Dependencies

All dependency are included in submodule

```cmd
git clone https://github.com/maidamai0/opengl_super_bible.git --recursively
```

* [glad](https://github.com/Dav1dde/glad)

  Load opengl functions, already in [deps/glad](deps/glad).

* [glfw](https://www.glfw.org/)

  Manage windows and OpenGL context

* [fmtlib](https://github.com/fmtlib/fmt)

  Replace std::cout,std::cerr, printf,sprintf...

* [glm](https://glm.g-truc.net/0.9.9/index.html)

  OpenGL math library

* [tinyply](https://glm.g-truc.net/0.9.9/index.html)

  PLY file reader

## Code style

All code is formated by [clang-format](https://clang.llvm.org/docs/ClangFormat.html) with default google style.

## Documentation

See [documentaion](./doc) for detail.

Some [PlantUML](https://plantuml.com/) code is used in documentation and GitHub markdown doesn't support it for now. So, I recommend rendering these markdown files by yourself with an editor support PlantUML embedded with PlantUML. VScode with a PlantUML extension is a good choice.
