#include "Text.hpp"

#include "Font.hpp"
#include "GL_CHECK_ERROR.hpp"
#include "OpenGL.hpp"
#include "Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <codecvt>
#include <iostream>
#include <locale>
#include <vector>

std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

void Text::SetString(const std::wstring& s) {
  string_ = s;
}

void Text::SetString(const std::string& s) {
  string_ = to_wstring(s);
}

void Text::SetFont(const Font& font) {
  font_ = &font;
}

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

class TextContext {
 private:
  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;
  GLuint vao, vbo;

 public:
  TextContext()
      : vertex_shader(P "./shader/shader.vert", GL_VERTEX_SHADER),
        fragment_shader(P "./shader/font.frag", GL_FRAGMENT_SHADER),
        program({vertex_shader, fragment_shader}) {
    struct VertexType {
      glm::vec2 position;
    };

    std::vector<VertexType> vertices{
        {glm::vec2(0.f, 0.f)}, {glm::vec2(0.f, 1.f)}, {glm::vec2(1.f, 1.f)},
        {glm::vec2(0.f, 0.f)}, {glm::vec2(1.f, 1.f)}, {glm::vec2(1.f, 0.f)},
    };

    // vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL_CHECK_ERROR(__FILE__, __LINE__);

    program.setAttribute("position", 2, sizeof(VertexType),
                         offsetof(VertexType, position));

    // vao end
    glBindVertexArray(0);
    GL_CHECK_ERROR(__FILE__, __LINE__);
  }

  void Draw(const glm::mat4& view, const Text& text) {
    GL_CHECK_ERROR(__FILE__, __LINE__);
    if (!text.font_)
      return;

    program.use();

    GL_CHECK_ERROR(__FILE__, __LINE__);
    glBindVertexArray(vao);

    float advance_x = 0.f;
    float advance_y = -text.font_->size;
    program.setUniform("color", text.GetColor());
    for (const auto& it : text.string_) {
      if (it == U'\n') {
        advance_x = 0.f;
        advance_y -= text.font_->size;
        continue;
      }
      auto character = text.font_->characters.find(it);
      if (character == text.font_->characters.end())
        continue;
      float dx = character->second.bearing.x;
      float dy = character->second.bearing.y;
      program.setUniform(
          "view",
          view *
              glm::translate(glm::mat4(),
                             glm::vec3(advance_x + dx, advance_y + dy, 0.0)) *
              text.GetTransformation(character->second.texture.width,
                                     character->second.texture.height));
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, character->second.texture.id);
      program.setUniform("tex", 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      advance_x += character->second.advance;
    }
    GL_CHECK_ERROR(__FILE__, __LINE__);
  }
};

namespace {
TextContext* context = nullptr;
}  // namespace

void Text::Draw(const glm::mat4& view) const {
  if (!context)
    context = new TextContext();
  context->Draw(view, *this);
}
