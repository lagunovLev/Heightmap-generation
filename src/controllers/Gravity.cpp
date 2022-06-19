#include "Gravity.h"


Gravity::Gravity(Camera* camera, float speed, float*** heights, size_t size)
{
	this->camera = camera;
	this->speed = speed;
	this->heights = *heights;
	this->size = size;
	this->motion = 0;

	this->lastTime = glfwGetTime();
	this->delta = 0.0f;

	this->camX = 0.0;
	this->camY = 0.0;
}

void Gravity::Control()
{
	float currentTime = glfwGetTime();
	delta = currentTime - lastTime;
	lastTime = currentTime;

	if (Events::pressed(GLFW_KEY_S))
		camera->position -= camera->front * speed * delta;
	if (Events::pressed(GLFW_KEY_W))
		camera->position += camera->front * speed * delta;
	if (Events::pressed(GLFW_KEY_A))
		camera->position -= camera->right * speed * delta;
	if (Events::pressed(GLFW_KEY_D))
		camera->position += camera->right * speed * delta;
	if (Events::_cursor_locked)
	{
		camX += -Events::deltaY / Window::height;
		camY += -Events::deltaX / Window::height;

		if (camX < -radians(89.0f))
			camX = -radians(89.0f);
		if (camX > radians(89.0f))
			camX = radians(89.0f);

		camera->rotation = mat4(1.0f);
		camera->rotate(camX, camY, 0);
	}

	motion += 0.003;
	float height = heights[(int)camera->position.x][(int)camera->position.z];
	if (camera->position.y <= height + 5)
	{
		motion = 0;
		camera->position.y = height + 5;
	}
	if (Events::jpressed(GLFW_KEY_SPACE))
		motion -= 0.5;
	camera->position.y -= motion;
}
