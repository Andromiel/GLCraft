#pragma once

#include "Registry.h"
#include "Block.h"

class BlockRegistry {
public:
	static inline Registry<Block> BLOCK_REGISTRY = Registry<Block>();//Registry<Block>();
	static inline short AIR = BLOCK_REGISTRY.Register(new Block(false, true));//BLOCK_REGISTRY.Register(Block(false, true));
	static inline short STONE = BLOCK_REGISTRY.Register(new Block(true, false));//BLOCK_REGISTRY.Register(Block(true, false));
};