// By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
// 
//	3
//	7 4
//	2 4 6
//	8 5 9 3
// 
// That is, 3 + 7 + 4 + 9 = 23.
// 
// Find the maximum total from top to bottom of the triangle below :
// 
//	75
//	95 64
//	17 47 82
//	18 35 87 10
//	20 04 82 47 65
//	19 01 23 75 03 34
//	88 02 77 73 07 63 67
//	99 65 04 28 06 16 70 92
//	41 41 26 56 83 40 80 70 33
//	41 48 72 33 47 32 37 16 94 29
//	53 71 44 65 25 43 91 52 97 51 14
//	70 11 33 28 77 73 17 78 39 68 17 57
//	91 71 52 38 17 14 91 43 58 50 27 29 48
//	63 66 04 68 89 53 67 30 73 16 69 87 40 31
//	04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Node.h"

#define FILE_NAME "e18_input.txt"

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
	Node_ptr root_node (new Node(input_lines[0][0], 0, 0, input_lines[0][0]));
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

	//// Finding the max path...
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
