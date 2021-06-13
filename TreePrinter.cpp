#pragma once
#include "TreePrinter.hpp"
#include <vector>

TreePrinter::TreePrinter(BST* tree) : tree(tree) {

}

int TreePrinter::countNodes(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	// Starts from 1 to include current node
	return 1 + countNodes(root->getLeftChild()) + countNodes(root->getRightChild());
}

int TreePrinter::digits(int num) {
	// Devide with 10 to get each digit
	if (num / 10 == 0) {
		return 1;
	}

	return 1 + digits(num / 10);
}

int TreePrinter::treeDigits(Node* root) {
	// If the node does not exist it would not have a key
	if (root == nullptr) {
		return 0;
	}

	// Count the digits of the subtrees
	int count = treeDigits(root->getLeftChild());
	count += treeDigits(root->getRightChild());
	count += digits(root->getKey());

	return count;
}

std::vector<struct nodeInfo *> TreePrinter::nodesCounts(std::vector<Node*> levelOrder) {
	std::vector<struct nodeInfo*> infos;

	// For every node in the tree, calculate the number of the
	// children of the left subtree and the number of children of the
	// right subtree
	for (auto& node : levelOrder) {
		struct nodeInfo* info = new nodeInfo;

		if (node != nullptr) {
			info->leftCount = countNodes(node->getLeftChild());
			info->rightCount = countNodes(node->getRightChild());
		}
		else {
			// If the node does not exists, it will have zero children
			info->leftCount = 0;
			info->rightCount = 0;
		}

		infos.push_back(info);
	}

	return infos;
}