#include "Block.h"

Block::Block(bool visible, bool transparent)
{
	this->_visible = visible;
	this->_transparent = transparent;
}

Block::~Block()
{
}

bool Block::IsVisible()
{
	return _visible;
}
