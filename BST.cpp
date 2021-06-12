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