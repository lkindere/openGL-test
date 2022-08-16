#version 330 core

const int hasTexture = 1;

uniform int flags;
uniform vec4 lightColor;
uniform sampler2D image;

out vec4 FragColor;

in vec2 _texCoords;

void main()
{
    vec4 texColor = vec4(1.0f);
    if ((flags & hasTexture) != 0)
        texColor = texture(image, _texCoords);
	FragColor = lightColor * texColor;
}