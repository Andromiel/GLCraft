#pragma once

#include <stack>
#include <vector>
#include <string>

class Frame
{
private:
	struct Node {
		std::vector<Node*> childs;
		std::string name;
		double time = 0;

		void Clear() {
			while (!childs.empty())
			{
				Node* child = childs.back();
				child->Clear();
				delete child;
				childs.pop_back();
			}
		}

		Node* Copy() {
			Node* node = new Node();
			node->name = this->name;
			node->time = this->time;
			for (int i = 0; i < this->childs.size(); i++)
			{
				node->childs.push_back(this->childs[i]->Copy());
			}
			return node;
		}

		int GetChildIndex(Node* node) {
			for (int i = 0; i < childs.size(); i++)
			{
				if (node == childs[i]) return i;
			}
			return -1;
		}
	};

	Node* root;
	std::vector<Node*> nodePath;
	void WriteFrameStep(int indent, Node* node);

public:
	Frame();
	Frame(Frame& obj);
	~Frame();
	void Push(std::string name);
	void Pop(double time);
	void Show();
	void Clear();

};

