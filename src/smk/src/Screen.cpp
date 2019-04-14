/**
 * Screen.hpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * MIT
 */

#include <smk/Screen.hpp>

#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>
#include <thread>

#include <smk/GL_CHECK_ERROR.hpp>
#include <smk/Input.hpp>
#include <smk/OpenGL.hpp>
#include <smk/Shader.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/View.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#endif

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

namespace smk {

Screen::Screen() {}
Screen::Screen(int width, int height, const std::string& title)
    : width_(640), height_(480) {
  std::cout << "[Info] GLFW initialisation" << std::endl;

  // initialize the GLFW library
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init GLFW");
  }

  // setting the opengl version
#ifdef __EMSCRIPTEN__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // create the window_
  window_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);
  if (!window_) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window_");
  }

  glfwMakeContextCurrent(window_);

#ifndef __EMSCRIPTEN__
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(std::string("Could initialize GLEW, error = ") +
                             (const char*)glewGetErrorString(err));
  }
#endif

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  // Make the window_'s context current
  glfwMakeContextCurrent(window_);

  // opengl configuration
  //glEnable(GL_DEPTH_TEST);  // enable depth-testing
  //glDepthFunc(GL_LESS);  // depth-testing interprets a smaller value as "closer"

  // Alph transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  View default_view;
  default_view.SetCenter(320, 480);
  default_view.SetSize(640, 480);
  SetView(default_view);
}

Screen::Screen(Screen&& screen) {
  operator=(std::move(screen));
}

void Screen::operator=(Screen&& screen) {
  std::swap(window_, screen.window_);
  std::swap(width_, screen.width_);
  std::swap(height_, screen.height_);
  std::swap(time_, screen.time_);
}

void Screen::PoolEvents() {
  glfwPollEvents();
  Input::Update(window_);
}

void Screen::Display() {
  // Swap Front and Back buffers (double buffering)
  glfwSwapBuffers(window_);

  // Detect window_ related changes
  UpdateDimensions();

  time_ = glfwGetTime();
}

Screen::~Screen() {
  // glfwTerminate(); // Needed? What about multiple windows?
}

void Screen::UpdateDimensions() {
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size("canvas", &width_, &height_);
#else
  glfwGetWindowSize(window_, &width_, &height_);
#endif
  glViewport(0, 0, width_, height_);
}

void Screen::Draw(const Sprite& sprite) { sprite.Draw(view_mat_); }
void Screen::Draw(const Text& text) { text.Draw(view_mat_); }

void Screen::SetView(const View& view) {
  view_ = view;
  float tx = view_.x_ - view_.width_ / 2.f;
  float ty = view_.y_ - view_.height_ / 2.f;
  view_mat_ =
      glm::mat4(2.0 / 640, 0.0, 0.0, 0.0,                                //
                0.0, -2.f / 480, 0.0, 0.0,                               //
                0.0, 0.0, 1.0, 0.0,                                      //
                -1.0 - 2.0 * tx / 640, 1.0 - 2.0 * ty / 480, 0.0, 1.0);  //
}

void Screen::Clear(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace smk
