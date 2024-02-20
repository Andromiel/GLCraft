#include "Frame.h"
#include <iostream>

Frame::Frame()
{
}

Frame::Frame(Frame& obj)
{
	this->root = obj.root->Copy();
	this->nodePath.push_back(this->root);
	if (obj.nodePath.size() < 1) return;
	for (int i = 0; i < obj.nodePath.size() - 1; i++)
	{
		int childIndex = obj.nodePath[i]->GetChildIndex(obj.nodePath[i + 1]);
		this->nodePath.push_back(this->nodePath.back()->childs[childIndex]);
	}
}

Frame::~Frame()
{
	Clear();
}

void Frame::Push(std::string name)
{
	Node* newNode = new Node();
	newNode->name = name;

	if (!nodePath.empty()) {
		nodePath.back()->childs.push_back(newNode);
	}
	else {
		if (root != nullptr) {
			root->Clear();
			delete root;
		}
		root = newNode;
	}
	nodePath.push_back(newNode);
}

void Frame::Pop(double time)
{
	nodePath.back()->time = time;
	nodePath.pop_back();
}

void Frame::Show()
{
	std::cout << "Pretty graph : " << std::endl;
	WriteFrameStep(0, root);
}

void Frame::WriteFrameStep(int indent, Node* node) {
	std::cout << std::string(indent, '|') << "-" << node->name << "(time : " << node->time << "ms)" << std::endl;
	for (int i = 0; i < node->childs.size(); i++)
	{
		WriteFrameStep(indent + 1, node->childs[i]);
	}
}

void Frame::Clear()
{
	while (!nodePath.empty()) {
		nodePath.pop_back();
	}
	if(root != nullptr)
	{
		root->Clear();
		delete root;
	}
}
