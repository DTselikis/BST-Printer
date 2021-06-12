#pragma once

class Node {
private:
	int key;
	Node* leftChild;
	Node* rightChild;
	bool active;
public:
	Node(int key, bool active = true);
	~Node();

	int getKey();
	Node* getLeftChild();
	Node* getRightChild();
	bool isActive();

	void setLeftChild(Node* node);
	void setRigthChild(Node* node);
	void setKey(int key);
	
	void disable();
};