#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexturePos;

out vec2 ioTexturePos;
uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;
uniform vec2 uResolution;
uniform vec2 uModelSize;

void main()
{
    ioTexturePos = aTexturePos;

    vec3 pos = aPos;
    pos.y += uResolution.y - uModelSize.y;

    gl_Position = uProjection * uView * uModel * vec4(pos, 1.0);
}