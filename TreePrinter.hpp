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
	char **getFormatedOutput();

	int digits(int num);
	int treeDigits(Node* node);
	int insertDigits(char** buffer, int count, int level, Node* node);
public:
	TreePrinter(BST* tree);

	void print();
};