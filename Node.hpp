#pragma once

class Node {
private:
	int key;
	Node* leftChild;
	Node* rightChild;
	bool active;
	bool rerouted;
public:
	Node(int key, bool active = true);
	~Node();

	int getKey();
	Node* getLeftChild();
	Node* getRightChild();
	bool isActive();
	bool isRerouted();

	void setLeftChild(Node* node);
	void setRigthChild(Node* node);
	void setKey(int key);
	
	void disable();
	void setRerouted();
};