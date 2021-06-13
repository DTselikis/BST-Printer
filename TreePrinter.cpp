#pragma once
#include "TreePrinter.hpp"
#include <vector>
#include <stdlib.h>

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

std::vector<struct nodeInfo *> TreePrinter::digitsCounts(std::vector<Node*> levelOrder) {
	std::vector<struct nodeInfo*> infos;

	// For every node in the tree, calculate the number of the
	// digits of the subtree
	for (auto& node : levelOrder) {
		struct nodeInfo* info = new nodeInfo;

		if (node != nullptr) {
			info->leftCount = treeDigits(node->getLeftChild());
			info->rightCount = treeDigits(node->getRightChild());
		}
		else {
			// If the node does not exists, it will have zero digits
			info->leftCount = 0;
			info->rightCount = 0;
		}

		infos.push_back(info);
	}

	return infos;
}

int TreePrinter::insertDigits(char** buffer, int count, int level, Node* node) {
	// If the node does not exists it will have zero digits
	if (node == nullptr) {
		return 0;
	}

	int key = node->getKey();
	// Allocate memory to store char * representation of the key
	// + 1 for '\0'
	char* strKey = new char[digits(node->getKey()) + 1];
	// Convert key to char *
	_itoa(key, strKey, 10);
	// Copy alpharithmetic key to position buffer size * level
	// to go the specific row and + count for the column
	strncpy(buffer[level] + count, strKey, digits(node->getKey()));

	// Deallocate memory
	delete strKey;

	// Return the numbers of digits that have been written
	return digits(node->getKey());
}
