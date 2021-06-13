#pragma once
#include "TreePrinter.hpp"
#include "TreeVector.hpp"
#include <vector>
#include <iostream>
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

char **TreePrinter::getFormatedOutput() {
	TreeVector treeVector(this->tree);
	std::vector<Node*> levelOrder = treeVector.toLevelOrderArray();
	std::vector<struct nodeInfo*> infos;
	
	infos = digitsCounts(levelOrder);

	int totalDigits = treeDigits(this->tree->getRoot());
	int height = this->tree->getHeight();

	// Construct the output buffer and set the end point
	char** buffer = new char*[height];
	for (int i = 0; i < totalDigits; i++) {
		buffer[i] = new char[totalDigits + 1];
		buffer[i][totalDigits] = '\0';
	}

	// For the root of the tree
	int count = 0;
	// Fill with as many X as the number of digits of the left subtree
	for (int i = 0; i < infos[0]->leftCount; i++) {
		buffer[0][i] = 'X';
 	}
	// Then insert the digits of the node
	insertDigits(buffer, infos[0]->leftCount, 0, levelOrder[0]);
	// and add the digits of the lesf child and of current node.
	count += infos[0]->leftCount + digits(levelOrder[0]->getKey());
	// Fill with as many X as the number of digits of the right subtree
	for (int i = 0; i < infos[0]->rightCount; i++) {
		buffer[0][i + count] = 'X';
	}

	// For the rest of the tree, construct each row
	int nodesToPrint = 2;
	int printedNodes = 1;
	for (int level = 1; level < height; level++) {
		count = 0;
		// Each level has a different number of nodes
		for (int i = 0; i < nodesToPrint; i++) {
			int k;
			// Fill with as many X as the number of digits of the left subtree
			for (k = 0; k < infos[printedNodes]->leftCount; k++) {
				buffer[level][k + count] = 'X';
			}
			// Add the number of the digits of the left subtree
			count += k;
			// Insert the digits of current node
			count += insertDigits(buffer, count, level, levelOrder[printedNodes]);
			int j;
			// Fill with as many X as the number of digits of the right subtree
			for (j = 0; j < infos[printedNodes]->rightCount; j++) {
				buffer[level][j + count] = 'X';
			}
			// Add the number of the digits of the right subtree
			count += j;
			printedNodes++;

			// If we reached the last node of the level and there are still
			// empty positions in the row, fill them with X until the the end
			// of the row.
			if (i == nodesToPrint - 1) {
				for (count; count < totalDigits; count++) {
					buffer[level][count] = 'X';
				}
			}
			else {
				// Search every upper level in the given column to see
				// if there is an ancestor. If there is, fill with as
				// many X as the digits of the ancestor.
				bool flag = true;
				bool innerFlag = true;
				for (j = 0; j < level && flag == true; j++) {
					while (buffer[j][count] != 'X' && innerFlag == true) {
						buffer[level][count] = 'X';
						count++;
						// We know it will be only one ancestor
						flag = false;

						if (count >= totalDigits) {
							// If the row is filled
							innerFlag = false;
						}
					}
				}
			}

			// If we accessed every node
			if (printedNodes == levelOrder.size() - 1) {
				break;
			}
		}
		nodesToPrint <<= 1;
	}

	return buffer;
}

void TreePrinter::print() {
	char **output = getFormatedOutput();

	for (int level = 0; level < this->tree->getHeight(); level++) {
		std::cout << output[level] << std::endl;

		delete[] output[level];
	}
}