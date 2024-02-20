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
	ivec2 _chunkCoords;
	short _blocks[CHUNKHEIGHT * CHUNKSIZE * CHUNKSIZE];
	Mesh* _mesh;
	bool IsValidCoordinates(ivec3 pos);
	bool IsTouchingChunk(ivec3 pos);
	void GenerateBlockMesh(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, std::vector<vec3>* normals, ivec3 pos);
	void GenerateBlockMeshFace(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, std::vector<vec3>* normals, ivec3 pos, Orientation orientation);

public:
	Chunk(ivec2 coords);
	~Chunk();

	void FillChunk( void (*fillingFunc)(short* blocksArray, ivec2 chunkCoords));
	Block GetBlockAt(ivec3 pos);
	void GenerateMesh();
	Mesh* GetMesh();

	static int GetFlattenIndices(ivec3 pos);
	static int GetFlattenIndices(int x, int  y, int z);
};