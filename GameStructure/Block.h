#pragma once

enum class SOLID_BLOCK_TYPES{AIR = 0, STONE = 1, GRASS = 2};

struct Block {
	int _id;
	bool _transparent;
};