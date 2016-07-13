// By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
// 
// 3
// 7 4
// 2 4 6
// 8 5 9 3
// 
// That is, 3 + 7 + 4 + 9 = 23.
// 
// Find the maximum total from top to bottom in triangle.txt(right click and 'Save Link/Target As...'), 
// a 15K text file containing a triangle with one - hundred rows.
// 
// NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this problem,
// as there are 2^99 altogether! If you could check one trillion (10^12) routes every second it would take over twenty billion
// years to check them all. There is an efficient algorithm to solve it.; o)

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Node.h"

#define FILE_NAME "p067_triangle.txt"

using namespace std;

int main()
{
	// Read Input File
	map<int, vector<int>> input_lines;
	ifstream reader(FILE_NAME);

	if (reader.is_open())
	{
		int row = 0;
		string line;
		while (getline(reader, line))
		{
			vector<int> v;
			istringstream ss(line);
			int num;
			while (ss >> num)
			{
				v.push_back(num);
			}

			input_lines.insert(pair<int, vector<int>>(row++, v));
		}

		reader.close();
	}
	else
	{
		cout << "Unable to open the source file. Program terminated.\n";
		return 1;
	}

	// Create the tree
	vector<Node_ptr> tree;
	Node_ptr root_node(new Node(input_lines[0][0], 0, 0, input_lines[0][0]));
	tree.push_back(root_node);

	for (size_t r = 0; r < input_lines.size() - 1; r++)
	{
		auto roots = input_lines[r];
		auto chields = input_lines[r + 1];

		for (size_t c = 0; c < roots.size(); c++)
		{
			root_node = Node::get_node_by_position(tree, r, c);

			Node_ptr left_node = Node::get_node_by_position(tree, r + 1, c);
			if (left_node == nullptr)
			{
				int left_node_value = chields[c];
				left_node = Node_ptr(new Node(left_node_value, r + 1, c, root_node->current_sum + left_node_value));
			}
			else
			{
				if ((root_node->current_sum + left_node->value) > left_node->current_sum)
				{
					left_node->current_sum = root_node->current_sum + left_node->value;
				}
			}

			int rigth_node_value = chields[c + 1];
			Node_ptr rigth_node = Node_ptr(new Node(rigth_node_value, r + 1, c + 1, root_node->current_sum + rigth_node_value));

			root_node->left_node = left_node;
			root_node->right_node = rigth_node;

			tree.push_back(left_node);
			tree.push_back(rigth_node);
		}
	}


	// Finding Nemo...
	int max_path = 0;
	for (size_t i = 0; i < tree.size(); i++)
	{
		if (tree[i]->current_sum > max_path)
		{
			max_path = tree[i]->current_sum;
		}
	}

	cout << max_path << endl;

	return 0;
}
