#version 330 core
layout(location = 0) in vec2 v_pos;

out vec2 f_pos;

uniform mat4 v_mvp;

void main() {
    gl_Position = v_mvp * vec4(v_pos, 1.0, 1.0);
    f_pos = v_pos;
}