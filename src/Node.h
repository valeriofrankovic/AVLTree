/*
 * Node.h
 *
 *  Created on: Oct 31, 2016
 *      Author: valerio
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <iostream>

using namespace std;

class Node {
private:
	Node * parent;
	Node * left;
	Node * right;
	int value;
	int balance;
	int height;
public:
	Node(Node * parent, int value);

	virtual ~Node();

	int getBalance() const {
		return balance;
	}

	void setBalance(int balance) {
		this->balance = balance;
	}

	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
			this->height = height;
	}

	int getValue() const {
		return value;
	}

	void setValue(int value) {
		this->value = value;
	}

	Node * getParent() const{
		return parent;
	}

	void setParent(Node * parent) {
		this->parent = parent;
	}

	Node * getLeft() const{
		return left;
	}

	void setLeft(Node * left) {
		this->left = left;
	}

	Node * getRight(){
		return this->right;
	}

	void setRight(Node * right) {
		this->right = right;
	}
};

#endif /* NODE_H_ */
