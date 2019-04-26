layout(location = 0) in vec2 space_position;
layout(location = 1) in vec2 texture_position;

uniform mat4 view;

out vec2 f_texture_position;

void main() {
  f_texture_position = texture_position;
  gl_Position = view * vec4(space_position, 0.0, 1.0);
}
