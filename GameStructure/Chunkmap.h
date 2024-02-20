#pragma once

#include <unordered_map>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include "Chunk.h"
#include "../Rendering/Renderer.h"

struct Chunkmap {//coordinates are relative to chunks (for example (0, 0) or (57, -14) etc)
private:
	std::unordered_map<glm::ivec2, Chunk*> _map;
public:
	Chunkmap();
	~Chunkmap();

	bool IsChunkGenerated(glm::ivec2 coords);
	bool IsChunkLoaded(glm::ivec2 coords);
	void LoadChunk(glm::ivec2 coords);
	void UnloadChunk(glm::ivec2 coords);
	void Render(Renderer* renderer);
private:
	void CreateChunk(glm::ivec2 coords);
	void SaveChunk(glm::ivec2 coords);
	void LoadChunkFromSave(glm::ivec2 coords);
};