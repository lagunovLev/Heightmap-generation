#pragma once

#include <glm/glm.hpp>
using namespace glm;

class Camera {
	void updateVectors();
public:
	vec3 front;
	vec3 up;
	vec3 right;

	vec3 position;
	float fov;
	float near;
	float far;
	mat4 rotation;
	Camera(vec3 position, float fov, float near, float far);

	void rotate(float x, float y, float z);

	mat4 getProjection();
	mat4 getView();
};
