#pragma once

#include <glm/vec3.hpp>

class WorldGenerator
{
private:
	static const float threshold;
public:
	static short Generate(glm::vec3 pos);
};

