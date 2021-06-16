#pragma once
#include "BST.hpp"
#include "TreeVector.hpp"

BST::BST() : root(nullptr) {
	this->height = 0;
	this->disabledNodes = 0;
	this->totalNodes = 0;
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

int BST::getDisabledNodes() {
	return this->disabledNodes;
}

int BST::getTotalNodes() {
	return this->totalNodes;
}

Node* BST::getRoot() {
	return this->root;
}

Node* BST::rerouteDisabled(Node* node) {
	Node* current = node;

	Node* tmp;
	// If the disabled node hasn't been retouted before
	if (current->isRerouted() == false) {
		// Find the node with the minimum value
		tmp = Find_Min(current->getRightChild());
		// We know that this node will "replace" a node with
		// two childer, and also that this node has no children.
		// So we set as the left child of this node the left child
		// of the node to be "replaced".
		tmp->setLeftChild(current->getLeftChild());
		// If this node had a right child, we perform a deletion
		// and insertion of this child to update all the nodes
		if (tmp->getRightChild() != nullptr) {
			int tmp2 = tmp->getRightChild()->getKey();
			deleteNode(current, tmp->getRightChild()->getKey());
			insert(tmp, tmp2);
		}
		current->setRerouted();
	}
	else {
		// If the node has already been rerouted, we know that
		// we should go to the right subtree (because in the case of
		// deletion of a node with two children, we find the node with the
		// minimum value of the right subtree.
		tmp = current->getRightChild();
	}

	current = tmp;

	return current;
}

Node* BST::bstInsert(Node* root, int key) {
	if (root == nullptr) {
		// We reached a leaf so this is where we will
		// insert the new node
		return new Node(key);
	}

	Node* current = root;
	if (!current->isActive()) {
		current = rerouteDisabled(current);
	}

	if (key < current->getKey()) {
		// Key is less than the key of current node so it will
		// certainly be a left child
		current->setLeftChild(insert(current->getLeftChild(), key));
	}
	else {
		// Key is greater or equal than the key of current node so it will
		// certainly be a right child
		current->setRigthChild(insert(current->getRightChild(), key));
	}

	return current;
}

int BST::countNodes(Node* root) {
	if (root == nullptr) {
		return 0;
	}

	// Starts from 1 to include current node
	return 1 + countNodes(root->getLeftChild()) + countNodes(root->getRightChild());
}

Node* BST::isBalanced(Node* root) {
	// If there is no tree, it's certainly balanced
	if (root == nullptr) {
		return nullptr;
	}

	Node* tmp = nullptr;
	
	int leftCount = countNodes(root->getLeftChild());
	int rightCount = countNodes(root->getRightChild());

	if (leftCount > 0 && rightCount > 0) {
		// If subtree is unbalanced, return the node that corresponds to
		// that subtree
		if (leftCount >= 2 * rightCount || rightCount >= 2 * leftCount) {
			return root;
		}
	}

	// If not, search the other subtrees
	tmp = isBalanced(root->getLeftChild());
	if (tmp == nullptr) {
		tmp = isBalanced(root->getRightChild());
	}

	return tmp;
}

Node* BST::sortedArrayToBST(std::vector<int> *sorted, int start, int end) {
	if (start > end) {
		return nullptr;
	}

	int mid = (start + end) / 2;
	Node* root = new Node(sorted->at(mid));

	root->setLeftChild(sortedArrayToBST(sorted, start, mid - 1));
	root->setRigthChild(sortedArrayToBST(sorted, mid + 1, end));

	return root;
}

Node* BST::reconstruct(Node* root) {
	if (root == nullptr) {
		return nullptr;
	}

	TreeVector treeVector(this);
	std::vector<int> sorted = treeVector.toSortedArray();

	deleteTree(this->root);

	this->root = sortedArrayToBST(&sorted, 0, sorted.size() - 1);

	treeHeight(this->root);

	return this->root;
}

Node* BST::insert(Node* root, int key) {
	this->root = bstInsert(root, key);

	if (isBalanced(this->root) != nullptr) {
		this->root = reconstruct(this->root);
	}

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
	if (root == nullptr) {
		return nullptr;
	}

	Node* current;
	
	// The minimum value will be at the leftmost child
	current = root;
	while (current->getLeftChild() != nullptr) {
		// If the node is disabled, find the corresponded node
		if (!current->isActive()) {
			current = rerouteDisabled(current);
		}
		// Otherwise search the right subtree, as intended
		else {
			current = current->getLeftChild();
		}
	}

	return current;
}

Node* BST::Find_Max(Node* root) {
	if (root == nullptr) {
		return nullptr;
	}

	Node* current;

	// The maximum value will be at the rightmost child
	current = root;
	while (current->getRightChild() != nullptr) {
		// If the node is disabled, find the corresponded node
		if (!current->isActive()) {
			current = rerouteDisabled(current);
		}
		// Otherwise search the right subtree, as intended
		else {
			current = current->getRightChild();
		}
	}

	return current;
}

std::vector<Node*> BST::Find_Between(Node* root, int key1, int key2) {
	std::vector<Node*> values;
	
	// At a leaf node values will be empty
	// so no insertion will be done
	if (root == nullptr) {
		return values;
	}

	// If the node is disabled, find the corresponded node
	if (!root->isActive()) {
		root = rerouteDisabled(root);
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
			Node* tmp = root;
			root = root->getRightChild();
			delete tmp;
		}
		// If has only a left child, it will take it's place
		else if (root->getRightChild() == nullptr) {
			Node* tmp = root;
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

	// If the number of the disabled nodes is greated than
	// half of the nubmer of total nodes, tree needs reconstruction
	if (this->disabledNodes > this->totalNodes / 2 && this->treeHeight() >= 3) {
		this->root = reconstruct(this->root);
	}

	return this->root;
}