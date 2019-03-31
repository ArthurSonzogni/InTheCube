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

std::function<void()>
    registered_loop;
void loop_iteration() {
  registered_loop();
}

Screen::Screen(int width, int height, const std::string& title)
    : width_(640), height_(480), title_(title) {
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

  // create the window
  window = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window");
  }

  glfwMakeContextCurrent(window);

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

  // opengl configuration
  //glEnable(GL_DEPTH_TEST);  // enable depth-testing
  //glDepthFunc(GL_LESS);  // depth-testing interprets a smaller value as "closer"

  // Alph transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Screen::~Screen() {}

GLFWwindow* Screen::GetWindow() const {
  return window;
}

float Screen::GetTime() const {
  return time;
}

void Screen::Run() {
  // Make the window's context current
  glfwMakeContextCurrent(window);

  time = glfwGetTime();

  registered_loop = [&]() {
  // compute new time and delta time
#ifndef __EMSCRIPTEN__
    double sleep_duration = std::max(0.0, 1.0 / 30.0 - glfwGetTime() + time);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(int(1000.f * sleep_duration)));
#endif
    time = glfwGetTime();

    // Detect window related changes
    DetectWindowDimensionChange();

    Input::Update(window);

    // execute the frame code
    loop_();

    // Swap Front and Back buffers (double buffering)
    glfwSwapBuffers(window);

    // Pool and process events
    glfwPollEvents();
  };

#ifdef __EMSCRIPTEN__
  //emscripten_set_main_loop(loop_iteration, 0, 1);
  //emscripten_set_main_loop(loop_iteration, 30, 1);
  emscripten_set_main_loop(loop_iteration, 0, 1);
#else
  for (;;)
    loop_iteration();
#endif
  glfwTerminate();
}

void Screen::SetLoop(std::function<void()> loop) {
  loop_ = loop;
}

void Screen::DetectWindowDimensionChange() {
  int w, h;
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size("canvas", &w, &h);
#else
  glfwGetWindowSize(GetWindow(), &w, &h);
#endif

  dimensionChanged = (w != width_ or h != height_);
  if (dimensionChanged) {
    width_ = w;
    height_ = h;
    glViewport(0, 0, width_, height_);
  }
}

int Screen::Width() {
  return width_;
}

int Screen::Height() {
  return height_;
}

float Screen::GetWindowRatio() {
  return float(width_) / float(height_);
}

bool Screen::WindowDimensionChanged() {
  return dimensionChanged;
}

void Screen::Draw(const Sprite& sprite) { sprite.Draw(view_); }
void Screen::Draw(const Text& text) { text.Draw(view_); }

void Screen::SetView(const View& view) {
  float tx = view.x_ - view.width_ / 2.f;
  float ty = view.y_ - view.height_ / 2.f;
  view_ = glm::mat4(2.0 / 640, 0.0, 0.0, 0.0,                                //
                    0.0, 2.f / 480, 0.0, 0.0,                                //
                    0.0, 0.0, 1.0, 0.0,                                      //
                    -1.0 - 2.0 * tx / 640, 1.0 - 2.0 * ty / 480, 0.0, 1.0);  //
}

void Screen::Clear(glm::vec4 color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace smk
