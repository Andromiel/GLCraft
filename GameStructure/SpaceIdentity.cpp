#include "SpaceIdentity.h"

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

using namespace glm;

SpaceIdentity::SpaceIdentity() {
	_position = vec3();
	_rotation = quat();
	_scale = vec3(1);
}

void SpaceIdentity::setPosition(vec3 position) {
	_position = position * vec3(1, 1, -1);
}

void SpaceIdentity::moveAbsolute(vec3 position) {
	_position += position * vec3(1, 1, -1);
}

void SpaceIdentity::moveLocal(vec3 position) {
	_position += (position * vec3(1, 1, -1) * _scale) * _rotation;
}

void SpaceIdentity::setRotation(vec3 rotation) {
	quat xQuat = angleAxis(rotation.x, vec3(1, 0, 0));
	quat yQuat = angleAxis(rotation.y, vec3(0, 1, 0));
	quat zQuat = angleAxis(rotation.z, vec3(0, 0, 1));
	_rotation = xQuat * yQuat * zQuat;
}

void SpaceIdentity::rotate(vec3 rotation) {
	_rotation = quat(rotation / 180.0f) * _rotation;
}

void SpaceIdentity::setScale(vec3 scale) {
	_scale = scale;
}

void SpaceIdentity::scale(vec3 scale) {
	_scale *= scale;
}

vec3 SpaceIdentity::getPosition() {
	return _position;
}

quat SpaceIdentity::getRotation() {
	return _rotation;
}

vec3 SpaceIdentity::getScale() {
	return _scale;
}

mat4 SpaceIdentity::getTransformationMatrix() {
	return mat4_cast(_rotation) * glm::translate(mat4(1), _position) * glm::scale(mat4(1), _scale);
}

