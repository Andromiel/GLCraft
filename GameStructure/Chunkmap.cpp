#include "Chunkmap.h"
#include "WorldGenerator.h"
#include "../Profiler/Profiler.h"

Chunkmap::Chunkmap()
{
}

Chunkmap::~Chunkmap()
{
}

bool Chunkmap::IsChunkGenerated(glm::ivec2 coords)
{
	//todo: check from save file
	return false;
}

bool Chunkmap::IsChunkLoaded(glm::ivec2 coords)
{
	if (_map.contains(coords)) {
		return true;
	}
	return false;
}

void Chunkmap::LoadChunk(glm::ivec2 coords)
{
	if (IsChunkLoaded(coords)) return;
	if (IsChunkGenerated(coords)) {
		LoadChunkFromSave(coords);
		return;
	}

	CreateChunk(coords);
}

void Chunkmap::UnloadChunk(glm::ivec2 coords)
{
	if (!IsChunkLoaded(coords)) return;

	SaveChunk(coords);
	_map.erase(coords);
}

void Chunkmap::Render(Renderer* renderer)
{
	//render back to front can save some performance on GPU
	SpaceIdentity space;
	space.setScale(vec3(0.1, 0.1, 0.1));
	mat4x4 mvp;

	std::unordered_map<ivec2, Chunk*>::iterator it;
	for (it = _map.begin(); it != _map.end(); it++) {
		Chunk* chunk= it->second;
		ivec2 coords = it->first;
		space.setPosition(vec3(coords.x * CHUNKSIZE * 0.1, 0, coords.y * CHUNKSIZE * 0.1));
		mvp = renderer->GetCameraMatrix() * space.getTransformationMatrix();
		chunk->GetMesh()->Draw(renderer, &mvp);
	}
}

void Chunkmap::CreateChunk(glm::ivec2 coords)
{
	Profiler::PROFILER.Push("Creating one chunk");
	Chunk* newChunk = new Chunk(coords);
	newChunk->FillChunk(WorldGenerator::Generate);
	newChunk->GenerateMesh();
	_map.insert({ coords, newChunk });
	Profiler::PROFILER.Pop();
}

void Chunkmap::SaveChunk(glm::ivec2 coords)
{
	//todo: save chunks
}

void Chunkmap::LoadChunkFromSave(glm::ivec2 coords)
{
	//todo: load from save
}
