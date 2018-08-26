/*
 * Node.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: valerio
 */

#include "Node.h"

Node::Node(Node * parent, int value) {
	// TODO Auto-generated constructor stub
	this->parent = parent;
	this->left = NULL;
	this->right = NULL;
	this->value = value;
	this->balance = 0;
	this->height = 0;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

