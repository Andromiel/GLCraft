#include "WorldGenerator.h"
#include <glm/gtc/noise.hpp>
#include <iostream>
#include "BlockRegistry.h"

const float WorldGenerator::threshold = 0.5f;

short WorldGenerator::Generate(glm::vec3 pos)
{
	if (glm::perlin(pos * 0.1f) > threshold) {
		return BlockRegistry::STONE;
	}

	return BlockRegistry::AIR;
}
