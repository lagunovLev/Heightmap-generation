#pragma once

#include "../window/Events.h"
#include "../window/Camera.h"

class Fly
{
	float lastTime;
	float delta;

	float camX;
	float camY;
public:
	Camera* camera;
	float speed;
	Fly(Camera* camera, float speed);
	void Control();
};