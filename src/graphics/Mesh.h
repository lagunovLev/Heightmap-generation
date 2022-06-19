#pragma once

#include <stdlib.h>
#include <glm/glm.hpp>

class Mesh
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	size_t vertices;
	size_t indices;
public:
	glm::mat4 model;
	Mesh(glm::mat4 model, float* vbo, int* attrs, size_t vertices, int* ebo, size_t indices);
	~Mesh();

	void draw(unsigned int primitive);
};
