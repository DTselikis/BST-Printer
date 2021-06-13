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
	std::vector<struct nodeInfo*> digitsCounts(std::vector<Node *> levelOrder);
	int digits(int num);
	int treeDigits(Node* node);
public:
	TreePrinter(BST* tree);

	void print();
};