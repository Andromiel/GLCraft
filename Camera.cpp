#include "Camera.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

using namespace glm;

Camera::Camera(int camWidth, int camHeight) {
	_fov = glm::radians(90.0f);
	_aspect = (float) camWidth / (float)camHeight;
	_near = 0.01f;
	_far = 1000.0f;
}

void Camera::setFieldOfView(float FOV) {
	_fov = glm::radians(FOV);
}

mat4 Camera::getProjectionMatrix() {
	return glm::perspective(_fov, _aspect, _near, _far);
}

mat4 Camera::getTransformationMatrix()
{
	return mat4_cast(_rotation) * glm::scale(mat4(1), _scale * vec3(1, 1, -1)) * glm::translate(mat4(1), _position * vec3(-1, -1, 1));
}
