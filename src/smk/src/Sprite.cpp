#include <smk/GL_CHECK_ERROR.hpp>
#include <smk/OpenGL.hpp>
#include <smk/Shader.hpp>
#include <smk/Sprite.hpp>
#include <vector>

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

namespace smk {

static Texture white_texture;
Texture* WhiteTexture() {
  if (white_texture.id == 0) {
    white_texture.width = 1;
    white_texture.height = 1;
    const uint8_t data[4] = {255, 255, 255, 255};
    glGenTextures(1, &white_texture.id);
    glBindTexture(GL_TEXTURE_2D, white_texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, white_texture.width,
                 white_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
  }
  return &white_texture;
}

class Sprite::Context {
 private:
  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;
  GLuint vao, vbo;

 public:
  Context()
      : vertex_shader(P "./shader/shader.vert", GL_VERTEX_SHADER),
        fragment_shader(P "./shader/shader.frag", GL_FRAGMENT_SHADER),
        program({vertex_shader, fragment_shader}) {
    struct VertexType {
      glm::vec2 space_position;
      glm::vec2 texture_position;
    };

    std::vector<VertexType> vertices{
        {glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f)},
        {glm::vec2(0.f, 1.f), glm::vec2(0.f, 1.f)},
        {glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f)},
        {glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f)},
        {glm::vec2(1.f, 1.f), glm::vec2(1.f, 1.f)},
        {glm::vec2(1.f, 0.f), glm::vec2(1.f, 0.f)},
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
    program.setAttribute("space_position", 2, sizeof(VertexType),
                         offsetof(VertexType, space_position));
    program.setAttribute("texture_position", 2, sizeof(VertexType),
                         offsetof(VertexType, texture_position));
    program.setUniform("tex", 0);
    program.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
    program.setUniform("view", glm::mat4(1.0));

    // vao end
    glBindVertexArray(0);
  }

  void Draw(const glm::mat4& view, const Sprite& sprite) {
    static bool is_used = false;
    GL_CHECK_ERROR(__FILE__, __LINE__);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    program.use();
    program.setUniform("color", sprite.color());
    auto* texture = sprite.texture();
    if (!texture)
      texture = WhiteTexture();
    program.setUniform(
        "view", view * sprite.GetTransformation(texture->width,
                                                texture->height));
    texture->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
};

namespace {
Sprite::Context* context = nullptr;
}  // namespace

void Sprite::Draw(const glm::mat4& view) const {
  if (!context)
    context = new Context();
  context->Draw(view, *this);
}

//void Sprite::Draw(Screen& screen, RenderState render_state) const {
  //render_state.color *= GetColor();
  //render_state.view *= GetTransformation(texture_->width, texture_->height);
  //render_state.texture = texture_;
  //screen.Draw(render_state);
//}

}  // namespace smk
