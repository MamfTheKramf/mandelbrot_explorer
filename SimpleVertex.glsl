#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 complex_pos;

out vec3 cPosition;

uniform vec3 offset;

void main()
{
        cPosition = complex_pos;
        gl_Position = vec4(position,1.0);
}
