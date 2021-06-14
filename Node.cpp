#pragma once
#include "Node.hpp"

Node::Node(int key, bool active) : key(key), leftChild(nullptr), rightChild(nullptr), active(active) {
	this->rerouted = false;
}

Node::~Node() {
	this->leftChild = nullptr;
	this->rightChild = nullptr;
}

int Node::getKey() {
	return this->key;
}

Node* Node::getLeftChild() {
	return this->leftChild;
}

Node* Node::getRightChild() {
	return this->rightChild;
}

bool Node::isActive() {
	return this->active;
}

bool Node::isRerouted() {
	return this->rerouted;
}

void Node::setLeftChild(Node* node) {
	this->leftChild = node;
}

void Node::setRigthChild(Node* node) {
	this->rightChild = node;
}

void Node::disable() {
	this->active = false;
}

void Node::setRerouted() {
	this->rerouted = true;
}

void Node::setKey(int key) {
	this->key = key;
}