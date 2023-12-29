#pragma once
#include <string>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#include "../Camera.h"
struct PlayerInfo {
	std::string _name;
	glm::vec3 _coords;
	Camera _view;
};