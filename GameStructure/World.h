#pragma once
#include <string>

#include "Chunkmap.h"
struct World {
private:
	std::string _name;
	Chunkmap _map;
	
public:
	World(std::string name);
	~World();
};