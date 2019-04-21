#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <functional>
#include <string>

#include <glm/glm.hpp>

#include <smk/Input.hpp>
#include <smk/RenderState.hpp>
#include <smk/Shader.hpp>
#include <smk/VertexArray.hpp>
#include <smk/View.hpp>

struct GLFWwindow;

namespace smk {

class Shape;
class Sprite;
class Text;
class View;
class VertexArray;

class Screen {
 public:
  Screen();
  Screen(int width, int height, const std::string& title);

  ~Screen();

  // Various data about the current window.
  int height() const { return height_; }
  int width() const { return width_; }
  float time() const { return time_; }
  GLFWwindow* window() const { return window_; }
  Input& input() { return input_; }

  // 0. Pool events. This updates the Input object.
  void PoolEvents();

  // 1. Clear the previous frame
  void Clear(const glm::vec4& color);

  // 2. Set the base view transformation.
  void SetView(const View& view);
  const View& GetView() const { return view_; }

  // 3. Draw.
  //void Draw(const Shape&)
  void Draw(const Sprite&);
  void Draw(const Text&);
  void Draw(const RenderState&);

  // 4. Notify the current frame is ready. The current and next one are swapped.
  void Display();

 private:
  GLFWwindow* window_ = nullptr;

  // Time:
  float time_ = 0.f;

  // Dimensions:
  int width_ = 0;
  int height_ = 0;

  // View:
  glm::mat4 view_mat_;
  smk::View view_;

  void UpdateDimensions();
  // -------- Movable only class.-----------------------------------------------
 public:
  Screen(Screen&&);          // Movable object
  void operator=(Screen&&);  // Movable object.
 private:
  Screen(const Screen&) = delete;          // Non copyable object.
  void operator=(const Screen&) = delete;  // Non copyable object.

  friend Sprite;
  VertexArray square_vertex_array_;
  VertexArray* square_vertex_array() { return &square_vertex_array_; }

  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;
  GLuint vao = 0;

  Input input_;
};

}  // namespace smk

#endif /* end of include guard: SCREEN_HPP */
