#pragma once
#include <stdlib.h>
#include <vector>
#include "../GameStructure/SpaceIdentity.h"
#include "VertexBuffers.h"
#include "IndexBuffer.h"
#include "Renderer.h"

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();
	void setVertices(vector<vec3>* vertices);
	void setIndices(vector<unsigned int>* indices);
	void Draw(Renderer* renderer, mat4* transformation);
	void Draw(Renderer* renderer);

private:
	vector<vec3> verticesPos;
	unsigned int verticesPosVBO;
	vector<unsigned int> indices;
	VertexBuffers* vertexBuffers;
	IndexBuffer* indexBuffer;
};

