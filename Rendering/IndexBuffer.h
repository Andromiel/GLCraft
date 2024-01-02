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
};

IndexBuffer::IndexBuffer() : _size(0) {
	glGenBuffers(1, &_ibo);
}

IndexBuffer::IndexBuffer(int size, unsigned int* data) :  _size(size * sizeof(unsigned int)) {
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::BufferData(int size, unsigned int* data) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, data, GL_DYNAMIC_DRAW);

	_size = size * sizeof(unsigned int);
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
}
