#pragma once
#include "BST.hpp"

class TreePrinter {
private:
	BST *tree;

	
	int countNodes(Node* root);
public:
	TreePrinter(BST* tree);

	void print();
};