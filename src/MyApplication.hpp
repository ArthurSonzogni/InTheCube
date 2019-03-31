/**
 * MyApplication.hpp skeleton
 * Contributors:
 *      * Arthur Sonzogni
 * Licence:
 *      * MIT
 */

#ifndef OPENGL_CMAKE_SKELETON_MYAPPLICATION
#define OPENGL_CMAKE_SKELETON_MYAPPLICATION

#include <smk/Screen.hpp>
#include "Shader.hpp"
#include "Level.hpp"

class MyApplication : public Screen {
 public:
  MyApplication();

 protected:
  virtual void loop();

 private:
  //float time = 0.f;
  const int size = 100;

  // shader
  Shader vertexShader;
  Shader fragmentShader;
  ShaderProgram shaderProgram;

  // shader matrix uniform
  glm::mat4 projection = glm::mat4(1.0);
  glm::mat4 view = glm::mat4(1.0);

  // VBO/VAO/ibo
  GLuint vao, vbo, ibo;

  Level level;
};

#endif  // OPENGL_CMAKE_SKELETON_MYAPPLICATION
