#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 complex_pos;

out vec3 cPosition;

uniform vec3 offset;
uniform mat4x4 scaling;

void main()
{
        cPosition = (scaling * vec4(complex_pos, 1.0)).xyz;
        gl_Position = vec4(position,1.0);
}
