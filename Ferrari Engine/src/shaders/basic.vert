#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform mat4 rot_matrix;

out DATA
{
	vec4 pos;
	vec4 colors;
} vs_out;

void main()
{
	gl_Position = pr_matrix * ml_matrix * rot_matrix * vw_matrix * position;
	vs_out.pos = ml_matrix * position;
	vs_out.colors = color;
}