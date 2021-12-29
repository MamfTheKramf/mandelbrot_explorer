#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vColor;
out vec3 vPosition;

uniform vec3 offset;

void main()
{
        vPosition = position + offset;
        vColor = color;
        gl_Position = vec4(vPosition,1.0);
}
