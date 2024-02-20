#include "WorldGenerator.h"
#include <glm/gtc/noise.hpp>
#include <iostream>
#include "BlockRegistry.h"
#include "Chunk.h"

const float WorldGenerator::threshold = 0.5f;

void WorldGenerator::Generate(short* blocksArray, glm::ivec2 chunkCoords)
{
	for (int x = 0; x < CHUNKSIZE; x++)
	{
		for (int z = 0; z < CHUNKSIZE; z++)
		{
			vec2 samplePoint = vec2(x + chunkCoords.x * CHUNKSIZE, z + chunkCoords.y * CHUNKSIZE);
			float height = 0;
			float amplitude = 0.5;
			float frequency = 0.01f;
			float persistence = 0.5f;
			float lacunarity = 2;
			float maxValue = 0;
			for (int i = 0; i < 4; i++) // octaves
			{
				height += perlin(samplePoint * frequency) * amplitude;
				maxValue += amplitude;
				frequency *= lacunarity;
				amplitude *= persistence;
			}
			height /= maxValue;
			height = (height + 1) / 2;
			height = height / 2;
;			int blockHeight = height * CHUNKHEIGHT;
			for (int y = 0; y < CHUNKHEIGHT; y++)
			{
				short block;
				if (y < blockHeight) block = BlockRegistry::STONE;
				else block = BlockRegistry::AIR;

				blocksArray[Chunk::GetFlattenIndices(x, y, z)] = block;
			}
		}
	}
}
