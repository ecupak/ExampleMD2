#version 310 es

uniform sampler2D skinTexture;

in mediump vec2 texCoord;

out mediump vec4 fragColor;


void main()
{
	fragColor = vec4(vec3(texture(skinTexture, texCoord)), 1.0);
}