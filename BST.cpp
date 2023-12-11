#include "BST.h"

BST::~BST()
{
    // Delete level by level
    int nodeCount = 0;

    std::queue<Node*> nodesInLevel;
    nodesInLevel.push(root);

    while (!nodesInLevel.empty())
    {
        nodeCount = nodesInLevel.size();
        while (nodeCount > 0)
        {
            Node* currentNode = nodesInLevel.front();

            if (currentNode->left != nullptr)
                nodesInLevel.push(currentNode->left);

            if (currentNode->right != nullptr)
                nodesInLevel.push(currentNode->right);
            
            delete currentNode;

            nodesInLevel.pop();
            nodeCount--;
        }
    }
}

void BST::insertNode(int value)
{
    if (root == nullptr)
        root = new Node(value);

    Node* currentNode = root;
    while (currentNode->value != value) // Does not allow duplicates
    {
        if (value < currentNode->value)
        {
            if (currentNode->left == nullptr)
                currentNode->left = new Node(value);

            currentNode = currentNode->left;
        }
        else
        {
            if (currentNode->right == nullptr)
                currentNode->right = new Node(value);
            
            currentNode = currentNode->right;
        }
    }
}

void BST::deleteNode(int value)
{
    if (root == nullptr)
        return;

    Node* previousNode = nullptr;
    Node* currentNode = root;
    while (currentNode != nullptr && currentNode->value != value)
    {
        previousNode = currentNode;
        if (value < currentNode->value)
            currentNode = currentNode->left;
        else if (value > currentNode->value)
            currentNode = currentNode->right;
    }

    if (currentNode == nullptr)
        return;

    // If we have at most one child
    if (currentNode->left == nullptr || currentNode->right == nullptr)
    {
        Node* newNode;

        if (currentNode->left != nullptr)
            newNode = currentNode->left;
        else
            newNode = currentNode->right;

        // If we are deleting root node
        if (previousNode == nullptr)
        {
            delete root;
            root = newNode;
            return;
        }

        if (currentNode == previousNode->left)
            previousNode->left = newNode;
        else
            previousNode->right = newNode;

        delete currentNode;
    }
    // Node has two children
    // We want to find smallest successor in the right subtree and put its value in the place of the deleted node
    else
    {
        Node* successorParent = nullptr;

        // Go into right subtree
        Node* successor = currentNode->right;

        // Find smallest value by going left
        while (successor->left != nullptr)
        {
            successorParent = successor;
            successor = successor->left;
        }
        
        if (successorParent != nullptr)
            successorParent->left = successor->right;
        else
            currentNode->right = successor->right;

        currentNode->value = successor->value;

        delete successor;
    }
}

std::string BST::getNodesAtLevel(int level)
{
    if (root == nullptr)
        return "Root of tree not initialized yet!";

    std::queue<Node*> nodesInLevel;
    int currentLevel = 0;
    int nodeCount = 0;

    nodesInLevel.push(root);
    while (!nodesInLevel.empty() && currentLevel != level)
    {
        currentLevel++;

        nodeCount = nodesInLevel.size();
        while (nodeCount > 0)
        {
            Node* currentNode = nodesInLevel.front();

            if (currentNode->left != nullptr)
                nodesInLevel.push(currentNode->left);

            if (currentNode->right != nullptr)
                nodesInLevel.push(currentNode->right);

            nodesInLevel.pop();
            nodeCount--;
        }
    }

    if (nodesInLevel.empty())
        return "No nodes at level " + std::to_string(level) + "!";

    std::string nodesAtLevel = "Nodes at level " + std::to_string(level) + ": ";
    while (!nodesInLevel.empty())
    {
        nodesAtLevel += std::to_string(nodesInLevel.front()->value) + ", ";

        nodesInLevel.pop();
    }

    nodesAtLevel.erase(nodesAtLevel.length() - 2, 2); // Erase last comma

    return nodesAtLevel;
}

int BST::getHeightFromNode(Node* node)
{
    if (node == nullptr)
        return 0;

    std::queue<Node*> nodesInLevel;
    int height = 0;
    int nodeCount = 0;

    nodesInLevel.push(node);
    while (!nodesInLevel.empty())
    {
        height++;

        nodeCount = nodesInLevel.size();
        while (nodeCount > 0)
        {
            Node* currentNode = nodesInLevel.front();

            if (currentNode->left != nullptr)
                nodesInLevel.push(currentNode->left);

            if (currentNode->right != nullptr)
                nodesInLevel.push(currentNode->right);

            nodesInLevel.pop();
            nodeCount--;
        }
    }
    return height;
}

int BST::getTreeHeight()
{
    return getHeightFromNode(root);
}

std::string BST::getDescendantsOfNode(int value)
{
    if (root == nullptr)
        return "Root of tree not initialized yet!";

    Node* searchedNode = root;
    while (searchedNode != nullptr && searchedNode->value != value)
    {
        if (value < searchedNode->value)
            searchedNode = searchedNode->left;
        else if (value > searchedNode->value)
            searchedNode = searchedNode->right;
    }

    if (searchedNode == nullptr)
        return "Node with value '" + std::to_string(value) +  "' not found!";

    int nodeCount = 0;

    std::queue<Node*> descendantNodes;

    std::queue<Node*> nodesInLevel;
    nodesInLevel.push(searchedNode);

    while (!nodesInLevel.empty())
    {
        nodeCount = nodesInLevel.size();
        while (nodeCount > 0)
        {
            Node* currentNode = nodesInLevel.front();

            if (currentNode->left != nullptr)
                nodesInLevel.push(currentNode->left);

            if (currentNode->right != nullptr)
                nodesInLevel.push(currentNode->right);

            if (currentNode != searchedNode)
                descendantNodes.push(currentNode);

            nodesInLevel.pop();
            nodeCount--;
        }
    }

    if (descendantNodes.empty())
        return "Node with value '" + std::to_string(value) + "' has no descendants!";

    std::string descendants = "Descendants of node with value '" + std::to_string(value) + "': ";
    while (!descendantNodes.empty())
    {
        descendants += std::to_string(descendantNodes.front()->value) + ", ";
        descendantNodes.pop();
    }

    descendants.erase(descendants.length() - 2, 2); // Erase last comma

    return descendants;
}

int BST::getQuantityOfUnbalancedNodes()
{
    int unbalancedNodes = 0;

    // Inorder traversal
    std::stack<Node*> s;
    Node* currentNode = root;
    while (currentNode != nullptr || !s.empty())
    {
        if (currentNode != nullptr)
        {
            s.push(currentNode);
            currentNode = currentNode->left;
        }

        currentNode = s.top();
        s.pop();

        int leftHeight = getHeightFromNode(currentNode->left);
        int rightHeight = getHeightFromNode(currentNode->right);

        if (std::abs(leftHeight - rightHeight) > 1)
            unbalancedNodes++;

        currentNode = currentNode->right;
    }

    return unbalancedNodes;
}

std::string BST::getAscendantsOfNode(int value)
{
    std::stack<Node*> s;
    Node* currentNode = root;

    while (currentNode != nullptr && currentNode->value != value)
    {
        s.push(currentNode);
        if (value < currentNode->value)
            currentNode = currentNode->left;
        else if (value > currentNode->value)
            currentNode = currentNode->right;
    }

    if (currentNode == nullptr)
        return "Node with value '" + std::to_string(value) + "' not found!";

    if (s.empty())
        return "Node with value '" + std::to_string(value) + "' has no ascendants!";

    std::string ascendants = "Ascendants of node with value '" + std::to_string(value) + "': ";
    while (!s.empty())
    {
        ascendants += std::to_string(s.top()->value) + ", ";
        s.pop();
    }

    ascendants.erase(ascendants.length() - 2, 2); // Erase last comma

    return ascendants;
}
