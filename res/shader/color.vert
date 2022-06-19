#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;

uniform mat4 model;
uniform mat4 projview;

out vec3 color;

void main()
{
	gl_Position = projview * model * vec4(v_position, 1.0);
	color = v_color;
}