#pragma once
#include <vector>
#include <glm/vec3.hpp>

#include "Block.h"

#define CHUNKSIZE 16

struct Chunk {
private:
	std::vector<Block> _blocks;
public:
	Chunk();
	~Chunk();

	void FillChunk( SOLID_BLOCK_TYPES* (*fillingFunc)(glm::ivec3, glm::ivec3));
};