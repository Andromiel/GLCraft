#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : _stride(0) {

}

VertexBufferLayout::~VertexBufferLayout() {

}

template<>
void VertexBufferLayout::Push<int>(int count) {
	_layout.push_back(LayoutElement(count, GL_INT));
	_stride += GetSize(GL_INT) * count;
}
template<>
void VertexBufferLayout::Push<float>(int count) {
	_layout.push_back(LayoutElement(count, GL_FLOAT));
	_stride += GetSize(GL_FLOAT) * count;
}
template<>
void VertexBufferLayout::Push<unsigned int>(int count) {
	_layout.push_back(LayoutElement(count, GL_UNSIGNED_INT));
	_stride += GetSize(GL_UNSIGNED_INT) * count;
}

const std::vector<LayoutElement>& VertexBufferLayout::GetLayout() {
	return _layout;
}

int VertexBufferLayout::GetStride() {
	return _stride;
}

int VertexBufferLayout::GetSize(int type) {
	switch (type) {
	case GL_INT: return 4;
	case GL_FLOAT: return 4;
	case GL_UNSIGNED_INT: return 4;
	case GL_UNSIGNED_BYTE: return 1;
	}
}