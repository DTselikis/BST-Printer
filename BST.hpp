#pragma once
#include "Node.hpp"

class BST {
private:
	Node* root;
	int height;
	int leftCount;
	int rightCount;
	int disabledNodes;
	int totalNodes;

	void deleteTree(Node* root);
	
	int bstTreeHeight(Node* root);
public:
	BST();
	~BST();

	int getHeight();
	int getLeftCount();
	int getRightCout();
	int getDisabledNodes();
	int getTotalNodes();

	void setRoot(Node* root);

	Node* insert(Node* root, int key);
	int treeHeight(Node* root);
	int treeHeight();
};