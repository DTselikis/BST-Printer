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

void BST::setRoot(Node* root) {
	this->root = root;
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

Node* BST::insert(Node* root, int key) {
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