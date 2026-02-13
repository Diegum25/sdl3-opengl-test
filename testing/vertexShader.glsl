#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 TexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = projection * view * model * vec4(aPos, 1.0); // MULTIPLICATION ORDER MATTERS WHAT THE FUCK

    pos.xy = floor((pos.xy * 10))/10; // lowk cool asf

    // dont know whats happening to .yz but i dont gaf
    // w is bad though

    gl_Position = pos;

    TexPos = aTexPos;
}