#pragma once
#include "TreeVector.hpp"
#include <queue>

TreeVector::TreeVector(BST* tree) : tree(tree) {
}

TreeVector::~TreeVector() {
	this->tree = nullptr;
}

std::vector<Node*> TreeVector::levelOrder(Node* root) {
	std::vector<Node*> vec;

	if (root == nullptr) {
		return vec;
	}

	// Create a queue to store children
	std::queue<Node*> queue;

	queue.push(root);

	while (queue.size() > 0) {
		// Each time the front child will be the next in the level order
		vec.push_back(queue.front());
		queue.pop();

		if (vec.back() != nullptr) {
			if (vec.back()->getLeftChild() != nullptr) {
				queue.push(vec.back()->getLeftChild());
			}
			else {
				// If there is no left child, store the null value
				// for future use
				queue.push(nullptr);
			}

			if (vec.back()->getRightChild() != nullptr) {
				queue.push(vec.back()->getRightChild());
			}
			else {
				// If there is no right child, store the null value
				// for future use
				queue.push(nullptr);
			}
		}
		
	}

	return vec;
}

std::vector<Node*> TreeVector::toLevelOrderArray() {
	return levelOrder(this->tree->getRoot());
}