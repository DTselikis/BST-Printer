#pragma once
#include "TreePrinter.hpp"

TreePrinter::TreePrinter(BST* tree) : tree(tree) {

}

int TreePrinter::countNodes(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	// Starts from 1 to include current node
	return 1 + countNodes(root->getLeftChild()) + countNodes(root->getRightChild());
}