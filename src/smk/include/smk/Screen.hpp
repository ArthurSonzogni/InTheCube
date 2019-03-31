#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <functional>
#include <glm/glm.hpp>
#include <string>

struct GLFWwindow;

namespace smk {

class Shape;
class Sprite;
class Text;
class View;

/// Screen class:
/// * init OpenGL
/// * provide:
///   * Width()
///   * Height()
///   * GetWindowRatio()
///   * windowDimensionChanged()
/// * let the user define the "loop" function.
class Screen {
 public:
  Screen(int width, int height, const std::string& title);
  ~Screen();

  // Get the window id
  GLFWwindow* GetWindow() const;

  float GetTime() const;

  // application run
  void Run();
  void SetLoop(std::function<void()> loop);

  void Clear(glm::vec4 color);

  // Screen informations
  int Width();
  int Height();
  float GetWindowRatio();
  bool WindowDimensionChanged();

  void Draw(const Shape& shape){};
  void Draw(const Sprite& sprite);
  void Draw(const Text& shape);
  void Display() {}

  void SetView(const View& view);

 private:
  Screen& operator=(const Screen&) { return *this; }

  GLFWwindow* window;

  // Time:
  float time;

  // Dimensions:
  int width_;
  int height_;

  bool dimensionChanged;
  void DetectWindowDimensionChange();

  std::function<void()> loop_;
  std::string title_;
  glm::mat4 view_;
};

}  // namespace smk

#endif /* end of include guard: SCREEN_HPP */
