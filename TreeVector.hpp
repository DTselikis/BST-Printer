#pragma once
#include "BST.hpp"
#include <vector>

class TreeVector {
private:
	BST* tree;

	std::vector<Node*> levelOrder(Node* root);

public:
	TreeVector(BST* tree);
	~TreeVector();

	std::vector<Node*> toLevelOrderArray();
};