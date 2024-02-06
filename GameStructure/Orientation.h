#pragma once

#include <glm/vec3.hpp>

enum Orientation
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};


static inline glm::ivec3 GetOffset(Orientation orientation) {
	switch (orientation)
	{
	case FORWARD:
		return glm::ivec3(0, 0, 1);
	case BACKWARD:
		return glm::ivec3(0, 0, -1);
	case RIGHT:
		return glm::ivec3(1, 0, 0);
	case LEFT:
		return glm::ivec3(-1, 0, 0);
	case UP:
		return glm::ivec3(0, 1, 0);
	case DOWN:
		return glm::ivec3(0, -1, 0);
	default:
		return glm::ivec3(0, 0, 1);
	}
}