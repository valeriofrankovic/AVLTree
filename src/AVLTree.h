/*
 * AVLTree.h
 *
 *  Created on: Oct 31, 2016
 *      Author: valerio
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "Node.h"
#include <string>
#include <iomanip>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

class AVLTree {
private:
	Node * root;
	void insertNode(Node * node, int value);
	void print(Node * node);
	void recursiveBalance(Node * node);
	void setBalance(Node * node);
	int height(Node * node);
	Node * rotateLeft(Node * node);
	Node * rotateRight(Node * node);
	Node * rotateLeftRight(Node * node);
	Node * rotateRightLeft(Node * node);
	void removeAVL(Node * node, int value);
	void removeFoundNode(Node * node);
	string intToString(int val);
	void adjustHeight(Node * node);
	void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out);
	void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out);
	void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out);
	void eraseTree(Node * node);
public:
	AVLTree();
	void insert(int value);
	void remove(int value);
	virtual ~AVLTree();

	Node*& getRoot() {
		return this->root;
	}

	void toString();
	void printPretty(Node * root, int level, int indentSpace, ostream& out);
};

#endif /* AVLTREE_H_ */
