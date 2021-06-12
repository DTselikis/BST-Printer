#pragma once
#include "BST.hpp"

BST::BST() : root(nullptr) {

}

BST::~BST() {
	if (this->root != nullptr) {
		deleteTree(this->root);
	}
}

// Preorder traversal of tree to delete
// every node
void BST::deleteTree(Node* root) {
	// When a leaf is reached return
	if (root != nullptr) {
		return;
	}

	// Delete left and right child
	deleteTree(root->getLeftChild());
	deleteTree(root->getRightChild());

	// Delete current node (father)
	delete root;
}

int BST::getHeight() {
	return this->height;
}

int BST::getLeftCount() {
	return this->leftCount;
}

int BST::getRightCout() {
	return this->rightCount;
}

int BST::getDisabledNodes() {
	return this->disabledNodes;
}

int BST::getTotalNodes() {
	return this->totalNodes;
}

Node* BST::getRoot() {
	return this->root;
}

Node* BST::bstInsert(Node* root, int key) {
	if (root == nullptr) {
		// We reached a leaf so this is where we will
		// insert the new node
		return new Node(key);
	}

	if (key < root->getKey()) {
		// Key is less than the key of current node so it will
		// certainly be a left child
		root->setLeftChild(insert(root->getLeftChild(), key));
	}
	else {
		// Key is greater or equal than the key of current node so it will
		// certainly be a right child
		root->setRigthChild(insert(root->getRightChild(), key));
	}

	return root;
}

Node* BST::insert(Node* root, int key) {
	this->root = bstInsert(root, key);

	return this->root;
}

int BST::bstTreeHeight(Node* root) {
	// Heigh of a leaf subtree is zero
	if (root == nullptr) {
		return 0;
	}
	else {
		// Find the heigh of each subtree
		int leftHeight = bstTreeHeight(root->getLeftChild());
		int rightHeight = bstTreeHeight(root->getRightChild());

		// Compare the heights of the two subtrees and find the
		// greater
		if (leftHeight > rightHeight) {
			return leftHeight + 1;
		}
		else {
			return rightHeight + 1;
		}
	}
}

int BST::treeHeight(Node* root) {
	int height = bstTreeHeight(root);
	this->height = height;

	return height;
}

int BST::treeHeight() {
	int height = treeHeight(this->root);

	return height;
}

Node* BST::Find_Min(Node* root) {
	Node* current;
	
	// The minimum value will be at the leftmost child
	for (current = root; current->getLeftChild() != nullptr; current = current->getLeftChild());

	return current;
}

Node* BST::Find_Max(Node* root) {
	Node* current;

	// The minimum value will be at the rightmost child
	for (current = root; current->getRightChild() != nullptr; current = current->getRightChild());

	return current;
}

std::vector<Node*> BST::Find_Between(Node* root, int key1, int key2) {
	std::vector<Node*> values;
	
	// At a leaf node values will be empty
	// so no insertion will be done
	if (root == nullptr) {
		return values;
	}

	// If our lowest value is less than this key it means that we
	// certainly need to go to the left subtree
	if (key1 < root->getKey()) {
		// Store all the values from the left subtree to a temp vector
		// and then contantinate them
		std::vector<Node *> tmp = Find_Between(root->getLeftChild(), key1, key2);
		values.insert(values.end(), tmp.begin(), tmp.end());
	}

	// If the key is in range, store is to the vector
	if (key1 <= root->getKey() && root->getKey() <= key2) {
		values.push_back(root);
	}

	// If our greatest value is greater than this key it means that we
	// certainly need to go to the right subtree
	if (key2 > root->getKey()) {
		// Store all the values from the left subtree to a temp vector
		// and then contantinate them
		std::vector<Node*> tmp = Find_Between(root->getRightChild(), key1, key2);
		values.insert(values.end(), tmp.begin(), tmp.end());
	}

	// In the end of each recursion each subtree will return all
	// the values of its subtrees if falls in range, plus his own
	// if falls in range
	return values;
}

Node* BST::bstDeleteNode(Node* root, int key) {
	if (root == nullptr) {
		return root;
	}

	// If key is less that current node's key we must
	// go to the left subtree
	if (key < root->getKey()) {
		root->setLeftChild(bstDeleteNode(root->getLeftChild(), key));
	}
	// If key is greater that current node's key we must
	// go to the right subtree
	else if (key > root->getKey()) {
		root->setRigthChild(bstDeleteNode(root->getRightChild(), key));
	}
	// We find the node
	else {
		// If it has no children we simple delete it
		if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr) {
			delete root;
			root = nullptr;
		}
		// If has only a right child, it will take it's place
		else if (root->getLeftChild() == nullptr) {
			struct Node* tmp = root;
			root = root->getRightChild();
			delete tmp;
		}
		// If has only a left child, it will take it's place
		else if (root->getRightChild() == nullptr) {
			struct Node* tmp = root;
			root = root->getLeftChild();
			delete tmp;
		}
		// If has two children, we mark it as disabled
		else {
			root->disable();
			this->disabledNodes++;
		}
	}

	return root;
}

Node* BST::deleteNode(Node* root, int key) {
	this->root = bstDeleteNode(root, key);

	return this->root;
}