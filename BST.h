#pragma once
class BST
{
private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;
	};

	Node* root;

public:
	BST(Node* root);

	~BST();

	void insertNode(Node* root, int value);
	void deleteNode(Node* root, int value);
	void displayNodesAtLevel(Node* root, int level);
	int getTreeHeight(Node* root);
	void displayDescendantsOfNode(Node* root, int value);
	// int getQuantityOfUnbalancedNodes(Node* root); (BONUS)
	// void displayAscendantsOfNode(Node* root, int value); (BONUS)
};

