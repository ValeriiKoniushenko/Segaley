#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;

out vec2 ioTexturePos;

void main()
{
    ioTexturePos = aTexturePos;

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}