#version 330 core
out vec4 FragColor;

in vec2 ioTexturePos;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture( uTexture, ioTexturePos );
} 