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

#include <smk/Color.hpp>
#include <smk/GL_CHECK_ERROR.hpp>
#include <smk/Input.hpp>
#include <smk/OpenGL.hpp>
#include <smk/RenderState.hpp>
#include <smk/Shader.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/VertexArray.hpp>
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

  square_vertex_array_ = VertexArray(std::vector<Vertex>({
      {glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f)},
      {glm::vec2(0.f, 1.f), glm::vec2(0.f, 1.f)},
      {glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f)},
      {glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f)},
      {glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f)},
      {glm::vec2(1.f, 0.f), glm::vec2(1.f, 0.f)},
  }));
}

Screen::Screen(Screen&& screen) {
  operator=(std::move(screen));
}

void Screen::operator=(Screen&& screen) {
  std::swap(window_, screen.window_);
  std::swap(width_, screen.width_);
  std::swap(height_, screen.height_);
  std::swap(time_, screen.time_);
  std::swap(square_vertex_array_, screen.square_vertex_array_);
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

void Screen::Draw(const Sprite& sprite) {
  RenderState state;
  state.view = view_mat_;
  state.color = smk::Color::White;
  state.vertex_array = nullptr;
  state.texture = nullptr;
  sprite.Draw(*this, state);
}

void Screen::Draw(const Text& text) {
  RenderState state;
  state.view = view_mat_;
  state.color = smk::Color::White;
  state.vertex_array = nullptr;
  state.texture = nullptr;
  text.Draw(*this, state);
}

Texture* WhiteTexture();

void Screen::Draw(const RenderState& state) {
  static Shader* vertex_shader = nullptr;
  static Shader* fragment_shader = nullptr;
  static ShaderProgram* program = nullptr;
  static GLuint vao = 0;

  if (!vertex_shader) {
    vertex_shader = new Shader(P "./shader/shader.vert", GL_VERTEX_SHADER);
    fragment_shader = new Shader(P "./shader/shader.frag", GL_FRAGMENT_SHADER);
    program = new ShaderProgram();
    program->AddShader(*vertex_shader);
    program->AddShader(*fragment_shader);
    program->Link();

    // vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    square_vertex_array()->Bind();
    program->use();
    program->setAttribute("space_position", 2, sizeof(Vertex),
                          offsetof(Vertex, space_position));
    program->setAttribute("texture_position", 2, sizeof(Vertex),
                          offsetof(Vertex, texture_position));
    program->setUniform("tex", 0);
    program->setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
    program->setUniform("view", glm::mat4(1.0));

    // vao end
    glBindVertexArray(0);
  }

  GL_CHECK_ERROR(__FILE__, __LINE__);

  glBindVertexArray(vao);
  state.vertex_array->Bind();
  program->use();
  program->setUniform("color", state.color);
  program->setUniform("view", state.view);
  auto* texture = state.texture;
  if (!texture)
    texture = WhiteTexture();
  texture->Bind();
  glDrawArrays(GL_TRIANGLES, 0, state.vertex_array->size());
}

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
