#pragma once
#include "Node.h"
#include <queue>
#include <string>
#include <stack>
#include <iostream>

class BST
{
private:
	Node* root;
	int getHeightFromNode(Node* node);

public:
	BST() : root(nullptr) {};

	~BST();

	void insertNode(int value);
	void deleteNode(int value);
	std::string getNodesAtLevel(int level);
	int getTreeHeight();
	std::string getDescendantsOfNode(int value);
	int getQuantityOfUnbalancedNodes();
	std::string getAscendantsOfNode(int value);
};

