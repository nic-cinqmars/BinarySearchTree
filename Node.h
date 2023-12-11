#pragma once
struct Node
{
	int value;
	Node* left;
	Node* right;

	Node(int value)
	{
		this->value = value;
		left = nullptr;
		right = nullptr;
	}
};