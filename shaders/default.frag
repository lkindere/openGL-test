#version 330 core

out vec4 FragColor;

in vec3 _color;

void main()
{
   FragColor = vec4(_color + vec3(0.1), 1.0f);
}