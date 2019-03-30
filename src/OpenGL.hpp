#ifndef OPENGL_HPP
#define OPENGL_HPP

#ifdef __EMSCRIPTEN__
  #include <GLES3/gl3.h>
  #include <emscripten/emscripten.h>
  #define GLFW_INCLUDE_ES3
  #include <GLFW/glfw3.h>
#else
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>
#endif

#endif /* end of include guard: OPENGL_HPP */
