#version 330 core
out vec4 pixColor;

in vec3 cPosition;

uniform vec3 rhombusPosition;
uniform float scalar;

int total_iterations = 512;

int mandelbrot(vec2 c) {
    int iteration = 0;
    vec2 curr = vec2(0.0, 0.0);

    while (length(curr) < 2.0 && iteration < total_iterations) {
        curr = vec2(curr.x * curr.x - curr.y * curr.y + c.x, 2 * curr.x * curr.y + c.y);
        iteration++;
    }
    return iteration;
}

void main()
{
        if (abs(cPosition.x - rhombusPosition.x) * 2 + abs(cPosition.y - rhombusPosition.y) < 0.03 * scalar) {
            pixColor = vec4(1.0, 1.0, 1.0, 1.0);
            return;
        }
        int it = mandelbrot(cPosition.xy);
        float r = float(1 * it % total_iterations) / float(total_iterations);
        float g = float(5 * it % total_iterations) / float(total_iterations);
        float b = float(2 * it % total_iterations) / float(total_iterations);
        pixColor = vec4(r, (g + r) / 2.0, (b + g) / 2.0, 1.0);
}
