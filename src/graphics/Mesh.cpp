#include "Mesh.h"
#include <iostream>
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>


Mesh::Mesh(glm::mat4 model, float* vbo, int* attrs, size_t vertices, int* ebo, size_t indices)
{
	this->vertices = vertices;
	this->model = model;
	this->indices = indices;
	int vertex_size = 0;
	for (int i = 0; attrs[i]; i++)
	{
		vertex_size += attrs[i];
	}

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, vbo, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices, ebo, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 0; attrs[i]; i++) {
		int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Mesh::draw(unsigned int primitive) {
	glBindVertexArray(vao);
	glDrawElements(primitive, indices / sizeof(int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}