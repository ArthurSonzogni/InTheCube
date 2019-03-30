in vec2 position;

uniform mat4 view;

out vec2 f_texture_position;

void main() {
  f_texture_position = position;
  gl_Position = view * vec4(position, 0.0, 1.0);
}
