#include "Mesh.h"

Mesh::Mesh()
{
	vertexBuffer = new VertexBuffer();
	indexBuffer = new IndexBuffer();
}

Mesh::~Mesh()
{
	delete indexBuffer;
	delete vertexBuffer;
}

void Mesh::setVertices(vector<float> vertices)
{
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->Push<float>(3);
	setVertices(vertices, layout);
}

void Mesh::setVertices(vector<float> vertices, VertexBufferLayout* layout)
{
	vertexBuffer->BufferData(vertices.size() * sizeof(float), vertices.data());
	vertexBuffer->SetLayout(layout);
}

void Mesh::setIndices(vector<unsigned int> indices)
{
	indexBuffer->BufferData(indices.size(), indices.data());
}

void Mesh::Draw(Renderer* renderer, mat4* transformation)
{
	vertexBuffer->Bind();
	indexBuffer->Bind();
	renderer->ResetUniform("matrix", transformation);
	renderer->Draw(indexBuffer->GetSize());
}

void Mesh::Draw(Renderer* renderer)
{
	mat4 mvp = mat4(0);
	Draw(renderer, &mvp);
}
