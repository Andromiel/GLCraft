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
	_position = vec3();
	_rotation = quat();
	_scale = vec3(1);
	_fov = glm::radians(90.0f);
	_aspect = (float) camWidth / (float)camHeight;
	_near = 0.01f;
	_far = 100.0f;
}

void Camera::setPosition(vec3 position) {
	_position = -position * vec3(1, 1, -1);
}

void Camera::moveAbsolute(vec3 position) {
	_position += -position * vec3(1, 1, -1);
}

void Camera::moveLocal(vec3 position) {
	_position += (-position * vec3(1, 1, -1)) * _rotation;
}

void Camera::setRotation(vec3 rotation) {
	rotation /= 180;
	quat xQuat = angleAxis(rotation.x, vec3(1, 0, 0));
	quat yQuat = angleAxis(rotation.y, vec3(0, 1, 0));
	quat zQuat = angleAxis(rotation.z, vec3(0, 0, 1));
	_rotation = xQuat * yQuat * zQuat;
}

void Camera::rotate(vec3 rotation) {
	_rotation = quat(rotation / 180.0f) * _rotation;
}

void Camera::setScale(vec3 scale) {
	_scale = scale;
}

void Camera::scale(vec3 scale) {
	_scale *= scale;
}

void Camera::setFieldOfView(float FOV) {
	_fov = glm::radians(FOV);
}

vec3 Camera::getPosition() {
	return _position;
}

quat Camera::getRotation() {
	return _rotation;
}

vec3 Camera::getScale() {
	return _scale;
}

mat4 Camera::getTransformationMatrix() {
	return mat4_cast(_rotation) * glm::scale(mat4(1), _scale) * glm::translate(mat4(1), _position);
}

mat4 Camera::getProjectionMatrix() {
	return glm::perspective(_fov, _aspect, _near, _far);
}