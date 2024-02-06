#pragma once

#include <unordered_map>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include "Chunk.h"

struct Chunkmap {//coordinates are relative to chunks (for example (0, 0) or (57, -14) etc)
private:
	std::unordered_map<glm::ivec3, Chunk> _map;
public:
	Chunkmap();
	~Chunkmap();

	bool ChunkExist(glm::vec3 coords);
	void CreateChunk(glm::ivec3 coords);
	void DeleteChunk(glm::ivec3 coords);
};