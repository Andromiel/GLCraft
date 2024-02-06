#include "Chunk.h"
#include <glm/vec3.hpp>
#include <iostream>
#include "BlockRegistry.h"
#include "Orientation.h"


bool Chunk::IsValidCoordinates(ivec3 pos)
{
	return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.x < CHUNKSIZE && pos.z < CHUNKSIZE && pos.y < CHUNKHEIGHT;
}

bool Chunk::IsTouchingChunk(ivec3 pos)
{
	return pos.x >= -1 && pos.y >= -1 && pos.z >= -1 && pos.x < CHUNKSIZE + 1 && pos.z < CHUNKSIZE + 1 && pos.y < CHUNKHEIGHT + 1;
}

void Chunk::GenerateBlockMesh(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, ivec3 pos)
{
	Block blockRendering = GetBlockAt(pos);
	if (!blockRendering.IsVisible()) return;
	GenerateBlockMeshFace(vertices, indices, pos, FORWARD);
	GenerateBlockMeshFace(vertices, indices, pos, BACKWARD);
	GenerateBlockMeshFace(vertices, indices, pos, RIGHT);
	GenerateBlockMeshFace(vertices, indices, pos, LEFT);
	GenerateBlockMeshFace(vertices, indices, pos, UP);
	GenerateBlockMeshFace(vertices, indices, pos, DOWN);
}

void Chunk::GenerateBlockMeshFace(std::vector<vec3>* vertices, std::vector<unsigned int>* indices, ivec3 pos, Orientation orientation)
{
	Block opositeBlock = GetBlockAt(pos + GetOffset(orientation)); //todo: Change GetBlockAt to get block on neighbour chunk
	if (opositeBlock.IsVisible()) return;
	unsigned int size = vertices->size();
	switch (orientation) {
	case FORWARD:
		vertices->insert(vertices->end(), {pos + ivec3(0, 0, 1), pos + ivec3(1, 0, 1), pos + ivec3(0, 1, 1), pos + ivec3(1, 1, 1)});
		break;
	case BACKWARD:
		vertices->insert(vertices->end(), { pos + ivec3(0, 0, 0), pos + ivec3(0, 1, 0), pos + ivec3(1, 0, 0), pos + ivec3(1, 1, 0) });
		break;
	case RIGHT:
		vertices->insert(vertices->end(), { pos + ivec3(1, 0, 0), pos + ivec3(1, 1, 0), pos + ivec3(1, 0, 1), pos + ivec3(1, 1, 1) });
		break;
	case LEFT:
		vertices->insert(vertices->end(), { pos + ivec3(0, 0, 0), pos + ivec3(0, 0, 1), pos + ivec3(0, 1, 0), pos + ivec3(0, 1, 1) });
		break;
	case UP:
		vertices->insert(vertices->end(), { pos + ivec3(0, 1, 0), pos + ivec3(0, 1, 1), pos + ivec3(1, 1, 0), pos + ivec3(1, 1, 1) });
		break;
	case DOWN:
		vertices->insert(vertices->end(), { pos + ivec3(0, 0, 0), pos + ivec3(1, 0, 0), pos + ivec3(0, 0, 1), pos + ivec3(1, 0, 1) });
		break;
	}
	indices->insert(indices->end(), { size + 0, size + 1, size + 2, size + 3, size + 2, size + 1 });
}

Chunk::Chunk()
{
	mesh = new Mesh();
}

Chunk::~Chunk()
{
}

void Chunk::FillChunk(short (*fillingFunc)(glm::vec3))
{
	_blocks.clear();
	for (int x = 0; x < CHUNKSIZE; x++)
	{
		for (int z = 0; z < CHUNKSIZE; z++)
		{
			for (int y = 0; y < CHUNKHEIGHT; y++)
			{
				short block = fillingFunc(glm::vec3(x, y, z));
				_blocks.push_back(block);
			}
		}
	}
}

Block Chunk::GetBlockAt(ivec3 pos)
{
	if (!IsValidCoordinates(pos)) {
		return BlockRegistry::BLOCK_REGISTRY->GetFromRegistry(BlockRegistry::AIR);
	}

	short blockId = _blocks.at(pos.x * CHUNKSIZE * CHUNKSIZE + pos.z * CHUNKSIZE + pos.y);
	return BlockRegistry::BLOCK_REGISTRY->GetFromRegistry(blockId);
}

void Chunk::GenerateMesh()
{
	std::vector<vec3>* vertices = new std::vector<vec3>;
	std::vector<unsigned int>* indices = new std::vector<unsigned int>;

	for (int x = 0; x < CHUNKSIZE; x++)
	{
		for (int z = 0; z < CHUNKSIZE; z++)
		{
			for (int y = 0; y < CHUNKHEIGHT; y++)
			{
				GenerateBlockMesh(vertices, indices, ivec3(x, y, z));
			}
		}
	}
	
	mesh->setVertices(vertices);
	mesh->setIndices(indices);
}

Mesh* Chunk::GetMesh()
{
	return mesh;
}
