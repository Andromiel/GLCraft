#include "Mesh.h"

Mesh::Mesh()
{
	vertexBuffers = new VertexBuffers();
	verticesPosVBO = vertexBuffers->AddBuffer<float>(3);

	indexBuffer = new IndexBuffer();
}

Mesh::~Mesh()
{
	delete indexBuffer;
	delete vertexBuffers;
}

void Mesh::setVertices(vector<vec3>* vertices)
{
	vector<float>* verticesFlatten = reinterpret_cast<vector<float>*>(vertices);
	vertexBuffers->BufferData<float>(verticesFlatten->size(), verticesFlatten->data(), verticesPosVBO);
}

VertexBuffers* Mesh::GetVertexBuffers()
{
	return vertexBuffers;
}

void Mesh::setIndices(vector<unsigned int>* indices)
{
	indexBuffer->BufferData(indices->size(), indices->data());
}

void Mesh::Draw(Renderer* renderer, mat4* transformation)
{
	if (indexBuffer->GetSize() == 0) return;
	vertexBuffers->BindLayout();
	indexBuffer->Bind();
	renderer->ResetUniform("matrix", transformation);
	renderer->Draw(indexBuffer->GetSize());
}

void Mesh::Draw(Renderer* renderer)
{
	mat4 mvp = mat4(0);
	Draw(renderer, &mvp);
}
