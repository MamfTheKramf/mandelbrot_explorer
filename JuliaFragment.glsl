#version 330 core
out vec4 pixColor;

in vec3 cPosition;

uniform vec3 c;

int julia(vec2 z0) {
    int iteration = 0;
    vec2 curr = z0;

    while (length(curr) < 2.0 && iteration < 256) {
        curr = vec2(curr.x * curr.x - curr.y * curr.y + c.x, 2 * curr.x * curr.y + c.y);
        iteration++;
    }
    return iteration;
}

void main()
{
        int it = julia(cPosition.xy);
        float r = float(5 * it % 256) / 256.0;
        float g = float(it) / 256.0;
        float b = float(it) / 256.0;
        pixColor = vec4(r, g, b, 1.0);
}
