#version 330 core
out vec4 pixColor;

in vec3 cPosition;

uniform vec3 rhombusColor;
uniform vec3 rhombusPosition;

int mandelbrot(vec2 c) {
    int iteration = 0;
    vec2 curr = vec2(0.0, 0.0);

    while (length(curr) < 2.0 && iteration < 256) {
        curr = vec2(curr.x * curr.x - curr.y * curr.y + c.x, 2 * curr.x * curr.y + c.y);
        iteration++;
    }
    return iteration;
}

void main()
{
        float it = float(mandelbrot(cPosition.xy)) / 256.0;
        pixColor = vec4(it, it, it, 1.0);
}
