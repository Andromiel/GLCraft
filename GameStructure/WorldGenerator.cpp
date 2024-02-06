#include "WorldGenerator.h"
#include <glm/gtc/noise.hpp>
#include <iostream>
#include "BlockRegistry.h"
#include "Chunk.h"

const float WorldGenerator::threshold = 0.5f;

short WorldGenerator::Generate(glm::vec3 pos)
{
	glm::vec2 coord = glm::vec2(pos.x, pos.z);
	float height = glm::perlin(coord * 0.05f);
	if (pos.y < (height + 1) / 2 * CHUNKHEIGHT) {
		return BlockRegistry::STONE;
	}

	return BlockRegistry::AIR;
}
