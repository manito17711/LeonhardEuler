#include "Node.h"

Node::Node(int v, int r, int c, int sum)
{
	this->current_sum = sum;
	this->row = r;
	this->column = c;
	this->value = v;
	this->left_node = nullptr;
	this->right_node = nullptr;
};

Node::Node(const Node & obj)
{
	this->current_sum = obj.current_sum;
	this->row = obj.row;
	this->column = obj.column;
	this->value = obj.value;
	this->left_node = obj.left_node;
	this->right_node = obj.right_node;
};

Node & Node::operator=(const Node & obj)
{
	this->current_sum = obj.current_sum;
	this->row = obj.row;
	this->column = obj.column;
	this->value = obj.value;
	this->left_node = obj.left_node;
	this->right_node = obj.right_node;

	return *this;
};

Node_ptr Node::get_node_by_position(const vector<Node_ptr>& vec, int r, int c)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i]->row == r && vec[i]->column == c)
		{
			return vec[i];
		}
	}

	return nullptr;
}
