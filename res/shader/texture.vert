#version 330 core

layout (location = 0) in vec3 Vertex;
layout (location = 1) in vec2 TexPos;

out vec2 texPos;
out vec3 vertex;
out vec4 pos;

uniform mat4 model;
uniform mat4 projview;

void main()
{
	texPos = TexPos;
	vertex = Vertex;
	gl_Position = projview * model * vec4(Vertex, 1.0);
	pos = gl_Position;
}