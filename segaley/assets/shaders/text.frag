#version 330 core

in vec2 ioTexCoords;
out vec4 oColor;

uniform sampler2D text;
uniform vec3 uTextColor;

void main()
{    
    vec4 sampled = vec4( 1.0, 1.0, 1.0, texture( text, ioTexCoords ).r );
    oColor = vec4( uTextColor, 1.0 ) * sampled;
}  