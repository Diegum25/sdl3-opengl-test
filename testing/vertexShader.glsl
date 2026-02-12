#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 TexPos;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = transform * projection * view * model * vec4(aPos, 1.0); // MULTIPLICATION ORDER MATTERS WHAT THE FUCK

    pos = floor((pos * 10))/10; // lowk cool asf

    // dont know whats happening to .zw but i dont gaf

    gl_Position = pos;

    TexPos = aTexPos;
}