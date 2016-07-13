#pragma once
#include <memory>
#include <vector>

using namespace std;

class Node;
typedef shared_ptr<Node> Node_ptr;

class Node
{
public:
	Node(int v, int r, int c, int sum);
	Node(const Node & obj);
	Node & operator=(const Node & obj);

	int current_sum;
	int row;
	int column;
	int value;

	Node_ptr left_node;
	Node_ptr right_node;

	static Node_ptr get_node_by_position(const vector<Node_ptr> & vec, int r, int c);
};

