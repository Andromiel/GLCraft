#pragma once

#include <GL/glew.h>

#include <vector>

class IndexBuffer {
private:
	unsigned int _ibo;
	int _size;

public:
	IndexBuffer();
	IndexBuffer(int size, unsigned int* data);

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer operator=(const IndexBuffer&) = delete;

	~IndexBuffer();

	void BufferData(int size, unsigned int* data);
	void Bind();
	int GetSize();
};
