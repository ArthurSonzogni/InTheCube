#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Font.hpp>
#include <smk/GL_CHECK_ERROR.hpp>
#include <smk/OpenGL.hpp>
#include <smk/Shader.hpp>
#include <smk/Text.hpp>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

namespace smk {

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

class Text::Context {
 private:
  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;
  GLuint vao, vbo;

 public:
  Context()
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
    float advance_y = -text.font_->size();
    program.setUniform("color", text.GetColor());
    for (const auto& it : text.string_) {
      if (it == U'\n') {
        advance_x = 0.f;
        advance_y -= text.font_->size();
        continue;
      }
      auto character = text.font_->GetCharacter(it);
      if (!character)
        continue;
      float dx = character->bearing.x;
      float dy = character->bearing.y;
      program.setUniform(
          "view",
          view *
              glm::translate(glm::mat4(),
                             glm::vec3(advance_x + dx, advance_y + dy, 0.0)) *
              text.GetTransformation(character->texture.width,
                                     character->texture.height));
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, character->texture.id);
      program.setUniform("tex", 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      advance_x += character->advance;
    }
    GL_CHECK_ERROR(__FILE__, __LINE__);
  }
};

void Text::Draw(const glm::mat4& view) const {
  context().Draw(view, *this);
}

Text::Context& Text::context() const {
  static Context* internal_context = nullptr;
  if (!internal_context)
    internal_context = new Context();
  return *internal_context;
}

}  // namespace smk
