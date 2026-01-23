#version 330 core
out vec4 FragColor;

in vec2 TexPos;

uniform sampler2D house;

void main()
{
   FragColor = texture(house, TexPos);
}