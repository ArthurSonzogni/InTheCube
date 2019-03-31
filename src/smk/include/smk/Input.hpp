#ifndef SMK_INPUT_HPP
#define SMK_INPUT_HPP

#include <map>

struct GLFWwindow;

namespace smk {

class Input {
 public:
  // update state
  static void Update(GLFWwindow* window);
  // keyboard
  static bool IsKeyPressed(int key);
  static bool IsKeyReleased(int key);
  static bool IsKeyHold(int key);
  // mouse
  static bool IsMousePressed(int key);
  static bool IsMouseReleased(int key);
  static bool IsMouseHold(int key);
  static double MouseX();
  static double MouseY();

  static void FixMouse();
  static void UnfixMouse();
  static bool IsMouseFixed();

  static float GetHorAngle();
  static float GetVerAngle();

  static bool IsIdle();
};

}  // namespace smk

#endif /* end of include guard: SMK_INPUT_HPP */
