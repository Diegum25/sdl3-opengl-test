#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
in vec3 FragPos;

void main()
{
    // Compute normal from triangle surface
    vec3 dx = dFdx(FragPos);
    vec3 dy = dFdy(FragPos);
    vec3 normal = normalize(cross(dx, dy));

    // Convert from [-1,1] to [0,1] for color
    vec3 color = normal * 0.5 + 0.5;

    FragColor = vec4(color, 1.0);
}