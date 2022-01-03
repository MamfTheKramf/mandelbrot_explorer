#version 330 core
out vec4 pixColor;

in vec3 cPosition;

uniform vec3 c;

int total_iterations = 512;

int julia(vec2 z0) {
    int iteration = 0;
    vec2 curr = z0;

    while (length(curr) < 2.0 && iteration < total_iterations) {
        curr = vec2(curr.x * curr.x - curr.y * curr.y + c.x, 2 * curr.x * curr.y + c.y);
        iteration++;
    }
    return iteration;
}

void main()
{
        int it = julia(cPosition.xy);
        float r = float(11 * it % total_iterations) / float(total_iterations);
        float g = float(1 * it % total_iterations) / float(total_iterations);
        float b = float(11 * it % total_iterations) / float(total_iterations);
        pixColor = vec4(r, sqrt(g), sqrt(b), 1.0);
}
