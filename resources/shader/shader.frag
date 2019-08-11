in vec2 f_texture_position;
uniform sampler2D tex;
uniform vec4 color;
out vec4 out_color;

void main() {
  out_color = texture(tex, f_texture_position) * color;
}
