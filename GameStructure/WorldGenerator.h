#pragma once

#include <glm/vec3.hpp>
#include "Chunk.h"

class WorldGenerator
{
private:
	static const float threshold;
public:
	static void Generate(short* blocksArray, glm::ivec2 chunkCoords);
};

