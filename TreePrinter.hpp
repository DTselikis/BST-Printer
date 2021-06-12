#pragma once
#include "BST.hpp"

struct nodeInfo {
	int leftCount = 0;
	int rightCount = 0;
};

class TreePrinter {
private:
	BST *tree;

	
	int countNodes(Node* root);
	std::vector<struct nodeInfo*> nodesCounts(std::vector<Node *> levelOrder);
public:
	TreePrinter(BST* tree);

	void print();
};