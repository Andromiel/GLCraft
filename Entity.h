#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class Entity {
	glm::vec3 m_pos;
	glm::vec3 m_velocity;
	glm::vec3 m_lookat;

	Entity(int a, int b, int c) : m_pos(a, b, c), m_velocity(0), m_lookat(0, 0, 1) {

	}

	~Entity() {

	}
};