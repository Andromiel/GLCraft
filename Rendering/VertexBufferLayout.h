#pragma once
#include <GL/glew.h>

#include <vector>

#include <glm/vec2.hpp>
struct LayoutElement {
	int count;
	int type;
	unsigned int vbo;
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
	void Push(int count, unsigned int vboToBind);

	template<> 
	void Push<int>(int count, unsigned int vboToBind);
	template<>
	void Push<float>(int count, unsigned int vboToBind);
	template<>
	void Push<unsigned int>(int count, unsigned int vboToBind);

};