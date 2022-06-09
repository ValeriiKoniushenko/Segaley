#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 ioTexCoords;

uniform mat4 uProjection;
uniform vec2 uResolution;
uniform float uFontSize;

void main()
{
    vec2 pos = vertex.xy;
    pos.y += uResolution.y - uFontSize;

    gl_Position = uProjection * vec4(pos, 0.0, 1.0);
    ioTexCoords = vertex.zw;
}  