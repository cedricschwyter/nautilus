#version 330 core
in vec2 f_pos;

out vec4 f_col;

void main() {
    f_col = vec4(f_pos, 0.0, 1.0);
}