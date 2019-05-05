/**
 * Shader.cpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * MIT
 */

#include <smk/Shader.hpp>

#include <cstdlib>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace smk {

using namespace glm;

const std::string shader_header =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
    "precision mediump float;\n"
    "precision mediump int;\n"
    "precision mediump sampler2DArray;\n";
#else
    "#version 330\n";
#endif

// file reading
bool getFileContents(const char* filename, std::vector<char>& buffer) {
  std::ifstream file(filename, std::ios_base::binary);
  if (file) {
    // Load shader header.
    for (const auto& c : shader_header)
      buffer.push_back(c);

    file.seekg(0, std::ios_base::end);
    std::streamsize size = file.tellg();
    if (size > 0) {
      file.seekg(0, std::ios_base::beg);
      buffer.resize(static_cast<size_t>(size + shader_header.size()));
      file.read(&buffer[shader_header.size()], size);
    }
    buffer.push_back('\0');
    return true;
  } else {
    std::cerr << "Cannot load " << filename << std::endl;
    return false;
  }
}

Shader::Shader() = default;
Shader::Shader(const std::string& filename, GLenum type) {
  // file loading
  std::vector<char> fileContent;
  getFileContents(filename.c_str(), fileContent);

  // creation
  handle_ = glCreateShader(type);
  if (handle_ == 0) {
    std::cerr << "[Error] Impossible to create a new Shader" << std::endl;
    throw std::runtime_error("[Error] Impossible to create a new Shader");
  }

  // code source assignation
  const char* shaderText(&fileContent[0]);
  glShaderSource(handle_, 1, (const GLchar**)&shaderText, NULL);

  // compilation
  glCompileShader(handle_);

  // compilation check
  GLint compile_status;
  glGetShaderiv(handle_, GL_COMPILE_STATUS, &compile_status);
  if (compile_status != GL_TRUE) {
    GLsizei logsize = 0;
    glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &logsize);

    char* log = new char[logsize + 1];
    glGetShaderInfoLog(handle_, logsize, &logsize, log);

    std::cout << "[Error] compilation error: " << filename << std::endl;
    std::cout << log << std::endl;

    exit(EXIT_FAILURE);
  } else {
    std::cout << "[Info] Shader " << filename << " compiled successfully"
              << std::endl;
  }
}

GLuint Shader::getHandle() const {
  return handle_;
}

Shader::~Shader() {
  if (!handle_)
    return;
  glDeleteShader(handle_);
  handle_ = 0;
}

Shader::Shader(Shader&& other) {
  this->operator=(std::move(other));
}

void Shader::operator=(Shader&& other) {
  std::swap(handle_, other.handle_);
}

ShaderProgram::ShaderProgram() = default;
void ShaderProgram::AddShader(const Shader& shader) {
  if (!handle_) {
    handle_ = glCreateProgram();
    if (!handle_)
      std::cerr << "[Error] Impossible to create a new Shader" << std::endl;
    std::cerr << "Created a handle" << std::endl;
  }
  glAttachShader(handle_, shader.getHandle());
}

void ShaderProgram::Link() {
  glLinkProgram(handle_);
  GLint result;
  glGetProgramiv(handle_, GL_LINK_STATUS, &result);
  if (result != GL_TRUE) {
    std::cout << "[Error] linkage error" << std::endl;

    GLsizei logsize = 0;
    glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &logsize);

    char* log = new char[logsize];
    glGetProgramInfoLog(handle_, logsize, &logsize, log);

    std::cout << log << std::endl;
  }
  std::cerr << "Link success" << std::endl;
}

GLint ShaderProgram::uniform(const std::string& name) {
  auto it = uniforms_.find(name);
  if (it == uniforms_.end()) {
    // uniforms_ that is not referenced
    GLint r = glGetUniformLocation(handle_, name.c_str());
    std::cerr << "new uniform " << name << std::endl;

    if (r == GL_INVALID_OPERATION || r < 0) {
      std::cerr << "[Error] uniform " << name << " doesn't exist in program"
                << std::endl;
    }
    // add it anyways
    uniforms_[name] = r;

    return r;
  } else
    return it->second;
}

GLint ShaderProgram::attribute(const std::string& name) {
  GLint attrib = glGetAttribLocation(handle_, name.c_str());
  if (attrib == GL_INVALID_OPERATION || attrib < 0)
    std::cerr << "[Error] Attribute " << name << " doesn't exist in program"
              << std::endl;

  return attrib;
}

void ShaderProgram::setAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLboolean normalize,
                                 GLenum type) {
  GLint loc = attribute(name);
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, size, type, normalize, stride,
                        reinterpret_cast<void*>(offset));
}

void ShaderProgram::setAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLboolean normalize) {
  setAttribute(name, size, stride, offset, normalize, GL_FLOAT);
}

void ShaderProgram::setAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLenum type) {
  setAttribute(name, size, stride, offset, false, type);
}

void ShaderProgram::setAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset) {
  setAttribute(name, size, stride, offset, false, GL_FLOAT);
}

void ShaderProgram::setUniform(const std::string& name,
                               float x,
                               float y,
                               float z) {
  glUniform3f(uniform(name), x, y, z);
}

void ShaderProgram::setUniform(const std::string& name, const vec3& v) {
  glUniform3fv(uniform(name), 1, value_ptr(v));
}

void ShaderProgram::setUniform(const std::string& name, const vec4& v) {
  glUniform4fv(uniform(name), 1, value_ptr(v));
}

void ShaderProgram::setUniform(const std::string& name, const mat4& m) {
  glUniformMatrix4fv(uniform(name), 1, GL_FALSE, value_ptr(m));
}

void ShaderProgram::setUniform(const std::string& name, const mat3& m) {
  glUniformMatrix3fv(uniform(name), 1, GL_FALSE, value_ptr(m));
}

void ShaderProgram::setUniform(const std::string& name, float val) {
  glUniform1f(uniform(name), val);
}

void ShaderProgram::setUniform(const std::string& name, int val) {
  glUniform1i(uniform(name), val);
}

ShaderProgram::~ShaderProgram() {
  if (!handle_)
    return;
  glDeleteProgram(handle_);
  handle_ = 0;
}

void ShaderProgram::use() const {
  glUseProgram(handle_);
}
void ShaderProgram::unuse() const {
  glUseProgram(0);
}

GLuint ShaderProgram::getHandle() const {
  return handle_;
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) {
  this->operator=(std::move(other));
}

void ShaderProgram::operator=(ShaderProgram&& other) {
  std::swap(handle_, other.handle_);
  std::swap(uniforms_, other.uniforms_);
}

}  // namespace smk