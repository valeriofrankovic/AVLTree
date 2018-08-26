/*
 * AVLTree.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: valerio
 */

#include "AVLTree.h"

AVLTree::AVLTree() {
	// TODO Auto-generated constructor stub
	this->root = NULL;

}

void AVLTree::insert(int value) {
	if (this->root != NULL) {
		insertNode(this->root, value);
	}
	else {
		Node * node = new Node(NULL, value);
		this->root = node;
	}
}

void AVLTree::insertNode(Node * parent, int value) {
	if (parent->getValue() > value) {
		if (parent->getLeft() == NULL) {
			parent->setLeft(new Node(parent, value));
			recursiveBalance(parent);
		}
		else {
			insertNode(parent->getLeft(), value);
		}
	}
	else if (parent->getValue() < value) {
		if (parent->getRight() == NULL) {
			parent->setRight(new Node(parent, value));
			recursiveBalance(parent);
		}
		else {
			insertNode(parent->getRight(), value);
		}
	}
}

void AVLTree::recursiveBalance(Node * node) {
	setBalance(node);

	if (node->getBalance() == -2) {

		if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight())) {
			node = rotateRight(node);
		}
		else {
			node = rotateLeftRight(node);
		}

	}
	else if (node->getBalance() == 2) {

		if (height(node->getRight()->getRight()) >= height(node->getRight()->getLeft())) {
			node = rotateLeft(node);
		}
		else {
			node = rotateRightLeft(node);
		}
	}

	if (node->getParent() != NULL) {
		recursiveBalance(node->getParent());
	}
	else {
		this->root = node;
	}

}

Node * AVLTree::rotateRight(Node * node) {
	Node * result = node->getLeft();

	result->setParent(node->getParent());

	node->setLeft(result->getRight());

	if(node->getLeft() != NULL) {
		node->getLeft()->setParent(node);
	}

	result->setRight(node);
	node->setParent(result);

	if(result->getParent() != NULL) {
		if (result->getParent()->getRight() == node) {
			result->getParent()->setRight(result);
		}
		else if (result->getParent()->getLeft() == node) {
			result->getParent()->setLeft(result);
		}
	}


	adjustHeight(node->getLeft());
	adjustHeight(node);
	adjustHeight(result);

	setBalance(node);
	setBalance(result);

	return result;
}

Node * AVLTree::rotateLeft(Node * node) {
	Node * result = node->getRight();
	result->setParent(node->getParent());

	node->setRight(result->getLeft());

	if(node->getRight() != NULL) {
		node->getRight()->setParent(node);
	}

	result->setLeft(node);
	node->setParent(result);

	if(result->getParent() != NULL) {
		if (result->getParent()->getRight() == node) {
			result->getParent()->setRight(result);
		}
		else if (result->getParent()->getLeft() == node) {
			result->getParent()->setLeft(result);
		}
	}


	adjustHeight(node->getLeft());
	adjustHeight(node);
	adjustHeight(result);

	setBalance(node);
	setBalance(result);

	return result;
}

Node * AVLTree::rotateLeftRight(Node * node) {
	node->setLeft(rotateLeft(node->getLeft()));
	Node * result = rotateRight(node);
	return result;
}

Node * AVLTree::rotateRightLeft(Node * node) {
	node->setRight(rotateRight(node->getRight()));
	Node * result = rotateLeft(node);
	return result;
}

void AVLTree::setBalance(Node * node) {
	node->setBalance(height(node->getRight()) - height(node->getLeft()));
}

void AVLTree::adjustHeight(Node * node) {
	if (node != NULL) {
		node->setHeight(1+max(height(node->getLeft()), height(node->getRight())));
	}
}

int AVLTree::height(Node * node) {
	if (!node) return 0;
	int leftHeight = height(node->getLeft());
	int rightHeight = height(node->getRight());
	return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

void AVLTree::remove(int value) {
	removeAVL(this->root, value);
}

void AVLTree::removeAVL(Node * node, int value) {
	if (!node) {
		return;
	}
	else {
		if (node->getValue() > value) {
			removeAVL(node->getLeft(), value);
		}
		else if (node->getValue() < value) {
			removeAVL(node->getRight(), value);
		}
		else {
			removeFoundNode(node);
		}
	}
}

void AVLTree::removeFoundNode(Node * node) {
	if (node->getLeft() != NULL) {
		Node * temp = node->getLeft();
		while (temp->getRight()) {
			temp = temp->getRight();
		}
		if (node->getLeft() == temp) {
			temp->getParent()->setLeft(temp->getLeft());
		}
		else {
			temp->getParent()->setRight(temp->getLeft());
		}
		node->setValue(temp->getValue());
		Node * rebalancing_required = temp->getParent();
		recursiveBalance(rebalancing_required);
		delete temp;
	}
	else if (node->getRight() != NULL) {
		Node * temp = node->getRight();
		while (temp->getLeft()) {
			temp = temp->getLeft();
		}
		if (node->getRight() == temp) {
			temp->getParent()->setRight(temp->getRight());
		}
		else {
			temp->getParent()->setLeft(temp->getRight());
		}
		node->setValue(temp->getValue());
		Node * rebalancing_required = temp->getParent();
		recursiveBalance(rebalancing_required);
		delete temp;
	}
	else {
		if (node == this->root) {
			delete node;
			this->root = NULL;
		}
		else {
			Node * rebalancing_required = node->getParent();
			if (node->getParent()->getRight() == node) {
				node->getParent()->setRight(NULL);
			}
			else {
				node->getParent()->setLeft(NULL);
			}
			delete node;
			recursiveBalance(rebalancing_required);
		}

	}
}


void AVLTree::toString() {
	if (this->root != NULL) {
		print(root);
		return;
	}
	else {
		cout << "" << endl;
	}
}

void AVLTree::print(Node * node) {
	if (node != NULL) {
		print(node->getLeft());
		cout << intToString(node->getValue()) + " ";
		print(node->getRight());
	}
	else cout << "";
}

// Convert an integer value to string
string AVLTree::intToString(int val) {
  ostringstream ss;
  ss << val;
  return ss.str();
}

void AVLTree::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {
    out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << endl;
}

void AVLTree::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->getLeft()) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? intToString((*iter)->getValue()) : "");
    out << ((*iter && (*iter)->getRight()) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}

void AVLTree::printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
  deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? intToString((*iter)->getValue()) : "");
  }
  out << endl;
}

void AVLTree::printPretty(Node *root, int level, int indentSpace, ostream& out) {
  int h = height(root);
  int nodesInThisLevel = 1;

  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

  deque<Node*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

    for (int i = 0; i < nodesInThisLevel; i++) {
      Node *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
	      nodesQueue.push_back(currNode->getLeft());
	      nodesQueue.push_back(currNode->getRight());
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

void AVLTree::eraseTree(Node * node) {
	if (node->getLeft()) {
		eraseTree(node->getLeft());
	}
	if (node->getRight()) {
		eraseTree(node->getRight());
	}
	delete node;
}

AVLTree::~AVLTree() {
	// TODO Auto-generated destructor stub
	eraseTree(this->root);
}

