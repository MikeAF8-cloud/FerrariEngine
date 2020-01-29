#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
	vec4 pos;
	vec4 colors;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.pos.xy - light_pos);
	color = colour * intensity;
	//color = fs_in.colors * intensity;
}