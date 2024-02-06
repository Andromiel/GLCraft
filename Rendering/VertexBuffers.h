#pragma once

#include <GL/glew.h>

#include <vector>

#include "VertexBufferLayout.h"

class VertexBuffers {
private:
	VertexBufferLayout* _layout;

public:
	VertexBuffers();

	VertexBuffers(const VertexBuffers&) = delete;
	VertexBuffers operator=(const VertexBuffers&) = delete;

	~VertexBuffers();

	template<typename T>
	unsigned int AddBuffer(int countByVertex);
	template<typename T>
	void BufferData(int size, T* data, unsigned int vbo);
	void BindLayout();
};

template<typename T>
unsigned int VertexBuffers::AddBuffer(int countByVertex) {
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	_layout->Push<T>(countByVertex, vbo);
	return vbo;
}

template<typename T>
void VertexBuffers::BufferData(int count, T* data, unsigned int vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * count, data, GL_DYNAMIC_DRAW);

}