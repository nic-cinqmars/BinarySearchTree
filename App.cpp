#include <iostream>
#include "BST.h"

int main()
{
	BST tree;
	char input;
	int value;
	
	do {
		std::cout << "- Enter one of the available commands -\n[I] - Insert, [D] - Delete, [L] - Level, [H] - Height, [A] - Ascendants, [B] - Descendants, [U] - Unbalanced nodes, [Q] - Quit : ";
		std::cin >> input;
		input = std::toupper(input);
		switch (input)
		{
		case 'I':
			std::cout << "Enter a value to enter in the tree: ";
			std::cin >> value;
			tree.insertNode(value);
			break;
		case 'D':
			std::cout << "Enter the value to be removed from the tree: ";
			std::cin >> value;
			tree.deleteNode(value);
			break;
		case 'L':
			std::cout << "Enter the level from which you want to see the nodes of: ";
			std::cin >> value;
			std::cout << tree.getNodesAtLevel(value);
			break;
		case 'H':
			std::cout << "Tree height: " << tree.getTreeHeight();
			break;
		case 'A':
			std::cout << "Enter a value to show its ascendants: ";
			std::cin >> value;
			std::cout << tree.getAscendantsOfNode(value);
			break;
		case 'B':
			std::cout << "Enter a value to show its descendants: ";
			std::cin >> value;
			std::cout << tree.getDescendantsOfNode(value);
			break;
		case 'U':
			std::cout << "Number of unbalanced nodes : " << tree.getQuantityOfUnbalancedNodes();
			break;
		default:
			std::cout << "Unknown command! Try again...";
		}
		std::cout << "\n\n";
	} while (input != 'Q');

	return 0;
}