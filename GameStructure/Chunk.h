#pragma once
#include <vector>
#include <glm/vec3.hpp>

#include "Block.h"
#include "Orientation.h"
#include "../Rendering/Mesh.h"

#define CHUNKSIZE 16
#define CHUNKHEIGHT 256

struct Chunk {
private:
	std::vector<short> _blocks;
	Mesh* mesh;
	bool IsValidCoordinates(ivec3 pos);
	bool IsTouchingChunk(ivec3 pos);
	void GenerateBlockMesh(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, ivec3 pos);
	void GenerateBlockMeshFace(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, ivec3 pos, Orientation orientation);

public:
	Chunk();
	~Chunk();

	void FillChunk( short (*fillingFunc)(glm::vec3));
	Block GetBlockAt(ivec3 pos);
	void GenerateMesh();
	Mesh* GetMesh();
};