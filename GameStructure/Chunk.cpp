#include "Chunk.h"
#include <glm/vec3.hpp>

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::FillChunk(SOLID_BLOCK_TYPES* (*fillingFunc)(glm::ivec3, glm::ivec3))
{
}
