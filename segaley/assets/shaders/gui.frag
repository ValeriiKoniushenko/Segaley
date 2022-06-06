#version 330 core
out vec4 FragColor;

uniform vec2 uResolution;
uniform vec4 uRectColor;
uniform vec2 uRectFrom;
uniform vec2 uRectTo;

float drawRect( vec2 from_, vec2 to_ )
{
    vec2 fragCoord = gl_FragCoord.xy / uResolution;

    vec2 from = vec2( from_.x, uResolution.y - from_.y ) / uResolution;
    vec2 to = vec2( to_.x, uResolution.y - to_.y ) / uResolution;

    vec2 kFrom = step( from, fragCoord );
    kFrom.y = kFrom.y == 0 ? 1 : 0;
    vec2 kTo = step( to, fragCoord );
    kTo.x = kTo.x == 0 ? 1 : 0;
    return kTo.x * kTo.y * kFrom.x * kFrom.y;
}

void main()
{
    FragColor = vec4( 0.f, 0.f, 0.f, 0.f );   

	FragColor = uRectColor * drawRect( uRectFrom, uRectTo );
} 