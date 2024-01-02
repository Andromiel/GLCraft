#pragma once

#include <GL/glew.h>

#include <vector>

#include "VertexBufferLayout.h"

class VertexBuffer {
private:
	unsigned int _vbo;
	int _size;
	VertexBufferLayout _layout;

public:
	VertexBuffer();
	VertexBuffer(int size, float* data);

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer operator=(const VertexBuffer&) = delete;

	~VertexBuffer();

	void BufferData(int size, float* data);
	void Bind();
	void SetLayout(VertexBufferLayout layout);
};

VertexBuffer::VertexBuffer() :_size(0) {
	glGenBuffers(1, &_vbo);
}

VertexBuffer::VertexBuffer(int size, float* data) : _size(size * sizeof(float)) {
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::BufferData(int size, float* data) {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_DYNAMIC_DRAW);

	_size = sizeof(float) * size;
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void VertexBuffer::SetLayout(VertexBufferLayout layout) {
	_layout = layout;
	int pointer = 0;
	for (int i = 0; i < layout.GetLayout().size(); i++) {
		const LayoutElement& layout_elt = layout.GetLayout()[i];
		glVertexAttribPointer(i, layout_elt.count, layout_elt.type, GL_FALSE, layout.GetStride(), (const void*)(pointer));
		glEnableVertexAttribArray(i);
		pointer += layout_elt.count * layout.GetSize(layout_elt.type);
	}
}