#version 330 core

const int hasTextures = 1;

uniform int modelFlags;
uniform vec4 lightColor;
uniform sampler2D image;

out vec4 FragColor;

in vec2 _texCoords;

void main()
{
    vec4 texColor = vec4(1.0f);
    if ((modelFlags & hasTextures) != 0)
        texColor = texture(image, _texCoords);
	FragColor = lightColor * texColor;
}