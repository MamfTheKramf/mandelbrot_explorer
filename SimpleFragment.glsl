#version 330 core
out vec4 pixColor;

in vec3 vColor;
in vec3 vPosition;

uniform vec3 rhombusColor;
uniform vec3 rhombusPosition;

void main()
{
        if(  abs(vPosition.x - rhombusPosition.x)
            +abs(vPosition.y - rhombusPosition.y) < 0.1) pixColor = vec4(rhombusColor, 1.0);
        else pixColor = vec4(vColor, 1.0);
}
