#pragma once
#include <stdlib.h>
#include <vector>
#include "../GameStructure/SpaceIdentity.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void setVertices(vector<float> vertices);
	void setVertices(vector<float> vertices, VertexBufferLayout* layout);
	void setIndices(vector<unsigned int> indices);
	void Draw(Renderer* renderer, mat4* transformation);
	void Draw(Renderer* renderer);

private:
	vector<float> vertices;
	vector<unsigned int> indices;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
};

