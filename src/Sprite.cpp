#include "Sprite.hpp"

#include "OpenGL.hpp"
#include "Shader.hpp"
#include "GL_CHECK_ERROR.hpp"
#include <vector>

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

class SpriteContext {
 private:
  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;
  GLuint vao, vbo;

 public:
  SpriteContext()
      : vertex_shader(P"./shader/shader.vert", GL_VERTEX_SHADER),
        fragment_shader(P"./shader/shader.frag", GL_FRAGMENT_SHADER),
        program({vertex_shader, fragment_shader}) {
    struct VertexType {
      glm::vec2 position;
    };

    std::vector<VertexType> vertices{
        {glm::vec2(0.f, 0.f)},
        {glm::vec2(0.f, 1.f)},
        {glm::vec2(1.f, 1.f)},

        {glm::vec2(0.f, 0.f)},
        {glm::vec2(1.f, 1.f)},
        {glm::vec2(1.f, 0.f)},
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

    program.use();
    program.setAttribute("position", 2, sizeof(VertexType),
                         offsetof(VertexType, position));
    program.setUniform("tex", 0);
    program.setUniform("color", glm::vec4(1.0,1.0,1.0,1.0));
    program.setUniform("view", glm::mat4(1.0));

    // vao end
    glBindVertexArray(0);
  }

  void Draw(const glm::mat4& view, const Sprite& sprite) {
    static unsigned int texture = -1;
    static bool is_used = false;
    //if (!is_used) {
      //is_used = true;
      GL_CHECK_ERROR(__FILE__, __LINE__);

      glBindVertexArray(vao);
      program.use();
    //}
    // send uniforms
    program.setUniform("color", sprite.GetColor());
    program.setUniform(
        "view", view * sprite.GetTransformation(sprite.texture_.width,
                                                 sprite.texture_.height));
    //if (texture != sprite.texture_.id) {
      texture = sprite.texture_.id;
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, sprite.texture_.id);
    //}

      glDrawArrays(GL_TRIANGLES, 0, 6);
  }
};

namespace {
SpriteContext* context = nullptr;
}  // namespace

void Sprite::SetTexture(Texture texture) {
  texture_ = texture;
}

void Sprite::Draw(const glm::mat4& view) const {
  if (!context)
    context = new SpriteContext();
  context->Draw(view, *this);
}
