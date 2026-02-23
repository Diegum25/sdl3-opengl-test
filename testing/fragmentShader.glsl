#version 330 core
out vec4 FragColor;

in vec2 TexPos;

uniform sampler2D house;
uniform float lightAmount;
uniform vec3 lightColour;

void main()
{

   vec4 light = vec4(lightAmount,lightAmount,lightAmount,1.0f) * vec4(lightColour,1.0f);

   FragColor = texture(house, TexPos) * light;
}