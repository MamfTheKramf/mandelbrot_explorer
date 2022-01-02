#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 complex_pos;

out vec3 cPosition;

uniform mat4x4 scaling;
uniform bool drawingJulia;

void main()
{
        cPosition = (scaling * vec4(complex_pos, 1.0)).xyz;
        vec3 shift;
        if (drawingJulia) {
            shift = vec3(0.5, 0, 0);
        } else {
            shift = vec3(-0.5, 0, 0);
        }
        gl_Position = vec4(position * 1 / 2 + shift,1.0);
}
