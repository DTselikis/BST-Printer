#pragma once
#include "Node.hpp"
#include <vector>

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
	Node* Find_Min(Node* root);
	Node* Find_Max(Node* root);
	std::vector<Node*> Find_Between(Node *root, int key1, int key2);
};