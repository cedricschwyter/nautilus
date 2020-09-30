#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nor;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 tan;
layout(location = 4) in vec3 bit;

out vec3 outPos;
out vec2 outTex;
out vec3 outNor;

uniform mat4 model;
uniform mat4 mvp;


void main() {
    gl_Position         = mvp * vec4(pos, 1.0);
    outTex              = tex;
    outPos              = vec3(model * vec4(pos, 1.0));
    outNor              = mat3(transpose(inverse(model))) * nor;
}
