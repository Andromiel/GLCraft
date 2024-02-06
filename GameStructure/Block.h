#pragma once

class Block {
private:
	bool _visible;
	bool _transparent;
public:
	Block(bool visible, bool transparent);
	~Block();
	bool IsVisible();
};