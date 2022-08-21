#version 330

out vec4 outColour;
in  vec2 passTextureCoord;
in float passCardinalLight;

uniform sampler2D texSampler;

void main()
{
    outColour = texture(texSampler, passTextureCoord) * passCardinalLight;
    //outColour = vec4(passTextureCoord.x,passTextureCoord.x,passTextureCoord.x,1);
    //if(outColour.a == 0) discard;
}