#pragma once

#include <GL/glew.h>

#include <vector>

#include "VertexBufferLayout.h"

class VertexBuffer {
private:
	unsigned int _vbo;
	int _size;
	VertexBufferLayout* _layout;

public:
	VertexBuffer();
	VertexBuffer(int size, float* data);

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer operator=(const VertexBuffer&) = delete;

	~VertexBuffer();

	void BufferData(int size, float* data);
	void Bind();
	void SetLayout(VertexBufferLayout* layout);
};