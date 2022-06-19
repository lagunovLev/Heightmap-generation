#include "Camera.h"
#include "Window.h"

#include <glm/ext.hpp>

Camera::Camera(vec3 position, float fov, float near, float far) : position(position), fov(fov), rotation(1.0f), near(near), far(far) {
	updateVectors();
}

void Camera::updateVectors() {
	front = vec3(rotation * vec4(0, 0, -1, 1));
	right = vec3(rotation * vec4(1, 0, 0, 1));
	up = vec3(rotation * vec4(0, 1, 0, 1));
}

void Camera::rotate(float x, float y, float z) {
	rotation = glm::rotate(rotation, z, vec3(0, 0, 1));
	rotation = glm::rotate(rotation, y, vec3(0, 1, 0));
	rotation = glm::rotate(rotation, x, vec3(1, 0, 0));

	updateVectors();
}

mat4 Camera::getProjection() {
	float aspect = (float)Window::width / (float)Window::height;
	return glm::perspective(fov, aspect, near, far);
}

mat4 Camera::getView() {
	return glm::lookAt(position, position + front, up);
}
