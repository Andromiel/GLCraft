#pragma once
#include <GL/glew.h>

#include <vector>

#include <glm/vec2.hpp>
struct LayoutElement {
	int count;
	int type;
};

class VertexBufferLayout {
private:
	std::vector<LayoutElement> _layout;
	int _stride;
	
public:
	VertexBufferLayout();
	~VertexBufferLayout();


	const std::vector<LayoutElement>& GetLayout();

	int GetStride();

	int GetSize(int type);

	template<typename T>
	void Push(int count);

	template<> 
	void Push<int>(int count);
	template<>
	void Push<float>(int count);
	template<>
	void Push<unsigned int>(int count);

};

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