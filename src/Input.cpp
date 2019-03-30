#include "Input.hpp"

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

namespace {
  std::map<int, std::pair<int, int>> keyState;
  std::map<int, std::pair<int, int>> mouseState;
  double m_mouseX;
  double m_mouseY;
  double m_mouseX_previous;
  double m_mouseY_previous;
  float horAngle = 0;
  float verAngle = 0;
  bool mouseIsFixed = false;
}

void Input::Update(GLFWwindow* window) {
#ifdef __EMSCRIPTEN__
  mouseIsFixed = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;

  static bool initialized = false;
  if (!initialized) {
    initialized = true;

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
#endif

  // get screen dimension
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // Update key
  for (auto it = keyState.begin(); it != keyState.end(); ++it) {
    it->second.second = it->second.first;
    it->second.first = glfwGetKey(window, it->first);
  }

  // Update mouse
  for (auto it = mouseState.begin(); it != mouseState.end(); ++it) {
    it->second.second = it->second.first;
    it->second.first = glfwGetMouseButton(window, it->first);
  }

  // get mouse position
  glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

  // get mouse position (bIs)
  horAngle = (float)(m_mouseX_previous - m_mouseX);
  verAngle = (float)(m_mouseY_previous - m_mouseY);

#ifndef __EMSCRIPTEN__
  // fix mousePosition
  if (mouseIsFixed) {
    m_mouseX = width/2;
    m_mouseY = height/2;
    glfwSetCursorPos(window, m_mouseX, m_mouseY);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
#endif

  m_mouseX_previous = m_mouseX;
  m_mouseY_previous = m_mouseY;
}

bool Input::IsKeyPressed(int key) {
  auto p = keyState[key];
  return ((p.first == GLFW_PRESS) and (p.second == GLFW_RELEASE));
}

bool Input::IsKeyReleased(int key) {
  auto p = keyState[key];
  return ((p.first == GLFW_RELEASE) and (p.second == GLFW_PRESS));
}

bool Input::IsKeyHold(int key) {
  auto p = keyState[key];
  return (p.first == GLFW_PRESS);
}

bool Input::IsMousePressed(int key) {
  auto p = mouseState[key];
  return ((p.first == GLFW_PRESS) and (p.second == GLFW_RELEASE));
}

bool Input::IsMouseReleased(int key) {
  auto p = mouseState[key];
  return ((p.first == GLFW_RELEASE) and (p.second == GLFW_PRESS));
}

bool Input::IsMouseHold(int key) {
  auto p = mouseState[key];
  return (p.first == GLFW_PRESS);
}

double Input::MouseX() {
  return m_mouseX;
}

double Input::MouseY() {
  return m_mouseY;
}

float Input::GetHorAngle() {
  return horAngle;
}

float Input::GetVerAngle() {
  return verAngle;
}

void Input::FixMouse() {
#ifndef __EMSCRIPTEN__
  mouseIsFixed = true;
#endif
}

void Input::UnfixMouse() {
#ifndef __EMSCRIPTEN__
  mouseIsFixed = false;
#endif
}
bool Input::IsMouseFixed() {
  return mouseIsFixed;
}
