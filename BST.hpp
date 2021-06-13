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
	Node* rerouteDisabled(Node* node);
	Node* isBalanced(Node* root);
	int countNodes(Node* root);
	Node* sortedArrayToBST(std::vector<int> sorted, int start, int end);
	
	int bstTreeHeight(Node* root);
	Node* bstDeleteNode(Node* root, int key);
	Node* bstInsert(Node* root, int key);
public:
	BST();
	~BST();

	int getHeight();
	int getLeftCount();
	int getRightCout();
	int getDisabledNodes();
	int getTotalNodes();
	Node* getRoot();

	Node* insert(Node* root, int key);
	int treeHeight(Node* root);
	int treeHeight();
	Node* Find_Min(Node* root);
	Node* Find_Max(Node* root);
	std::vector<Node*> Find_Between(Node *root, int key1, int key2);
	Node* deleteNode(Node* root, int key);
	Node* reconstruct(Node* root);
};