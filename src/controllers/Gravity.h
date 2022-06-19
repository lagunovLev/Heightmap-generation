#pragma once

#include "../window/Events.h"
#include "../window/Camera.h"

class Gravity
{
	float lastTime;
	float delta;

	float camX;
	float camY;

	size_t size;

	float motion;

	float** heights;
public:
	Camera* camera;
	float speed;
	Gravity(Camera* camera, float speed, float*** heights, size_t size);
	void Control();
};

