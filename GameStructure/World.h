#pragma once
#include <string>
#include "Chunkmap.h"

struct World {
private:
	std::string _name;
	Chunkmap* chunkMap;
	
public:
	World(std::string name);
	~World();
};