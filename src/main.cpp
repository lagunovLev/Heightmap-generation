#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "graphics/Mesh.h"
#include "window/Window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "loaders/png_loading.h"
#include "controllers/Fly.h"
#include "loaders/generate_map.h"
#include "controllers/Gravity.h"

int WIDTH = 1000;
int HEIGHT = 900;

size_t size = 1000;


int main() 
{
	srand(time(NULL));
	Window::initialize(WIDTH, HEIGHT, "Window 2.0");
	Events::initialize();

	float** heights = new float*[size];
	for (int i = 0; i < size; i++)
		heights[i] = new float[size];

	Shader* shader = load_shader("res/shader/texture.vert", "res/shader/texture.frag");
	Texture* texture = load_texture("res/texture/grass2.png");
	Mesh* mesh = generate_map(size, &heights);
	Camera* camera = new Camera(glm::vec3(size / 2, 20, size / 2), radians(40.0f), 0.1, 1000);
	Gravity* control = new Gravity(camera, 30, &heights, size);
	const glm::vec3 fogColor = { 0.5, 0.5, 0.5 };
	float yMotion = 0;

	glClearColor(fogColor.x, fogColor.y, fogColor.z, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	while (!Window::isShouldClose()) 
	{
		Events::pullEvents();

		if (Events::jpressed(GLFW_KEY_ESCAPE))
			break;
		if (Events::jpressed(GLFW_KEY_TAB))
			Events::toogleCursor();
		if (Events::jpressed(GLFW_KEY_SPACE))
			yMotion -= 0.5;
		
		control->Control();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();
		shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
		shader->uniform3f("camera", camera->position.x, camera->position.y, camera->position.z);
		shader->uniform3f("fogColor", fogColor.x, fogColor.y, fogColor.z);
		texture->bind();
		shader->uniformMatrix("model", mesh->model);
		mesh->draw(GL_TRIANGLES);

		Window::swapBuffers();
	}
	delete shader;
	delete texture;
	delete mesh;
	delete camera;
	delete control;
	for (int i = 0; i < size; i++)
		delete heights[i];
	delete heights;

	Window::terminate();
	return 0;
}
