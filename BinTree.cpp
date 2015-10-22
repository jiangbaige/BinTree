//
// Created by Shyawn Karim on 10/13/15.
//

#include "BinTree.h"

using namespace std;


// --------------------- Overloaded << -----------------------------------------
//
// --------------------------------------------------------------
ostream &operator<<(ostream &outStream, const BinTree &tree)
{
    tree.inorderHelper(tree.root);
    outStream << endl;
    return outStream;
}

//istream &operator>>(istream &inStream, BinTree &tree)
//{
//    return <#initializer#>;
//}

// --------------------- Default Constructor -----------------------------------------
//
// --------------------------------------------------------------
BinTree::BinTree()
{
    this->root = new Node();
    this->root->left = NULL;
    this->root->right = NULL;
}

// --------------------- Copy Constructor -----------------------------------------
//
// --------------------------------------------------------------
BinTree::BinTree(const BinTree &sourceTree)
{
    *this = sourceTree;
}

// --------------------- Destructor -----------------------------------------
//
// --------------------------------------------------------------
BinTree::~BinTree()
{
    this->makeEmpty();
}

// --------------------- isEmpty -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::isEmpty() const
{
    if (this->root == NULL)
    {
        return true;
    }

    return false;
}

// --------------------- makeEmpty -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::makeEmpty()
{
        makeEmptyHelper(root);
}

// --------------------- makeEmptyHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::makeEmptyHelper(Node* current)
{
    if (current != NULL)
    {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);

        delete current->data;
        current->data = NULL;
        delete current;
        current = NULL;
    }
}

// --------------------- Overloaded = -----------------------------------------
//
// --------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rTree)
{
    if (*this == rTree)
    {
        return *this;
    }

    this->makeEmpty();

    this->assignmentHelper(rTree.root);

    return *this;
}

// --------------------- assignmentHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::assignmentHelper(Node* current)
{
    if (current != NULL)
    {
        insert(current->data);
        assignmentHelper(current->left);
        assignmentHelper(current->right);
    }
}

// --------------------- Overloaded == -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::operator==(const BinTree &rTree) const
{
    if (this->root == NULL && rTree.root == NULL)
    {
        return true;
    }
    else
    {
        return equalityComparisonHelper(this->root, rTree.root);
    }
}

// --------------------- equalityComparisonHelper -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::equalityComparisonHelper(Node* lNode, Node* rNode) const
{
    if (lNode == NULL && rNode == NULL)
    {
        return true;
    }

    if (lNode == NULL || rNode == NULL)
    {
        return false;
    }

    if (*lNode->data == *rNode->data && lNode->left == NULL && rNode->left == NULL)
    {
        equalityComparisonHelper(lNode->left, rNode->left) &&
        equalityComparisonHelper(lNode->right, rNode->right);
    }
}

// --------------------- Overloaded != -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rTree) const
{
    return !(*this == rTree);
}

// --------------------- insert -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::insert(NodeData* toInsert)
{
    return insertHelper(this->root, toInsert);
}

// --------------------- insertHelper -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::insertHelper(Node*& current, NodeData* toInsert)
{
    if (this->root == NULL)
    {
        root = new Node;
        root->data = toInsert;
        root->left = NULL;
        root->right = NULL;
    }
    else if (*toInsert < *root->data)
    {
        insertHelper(root->left, toInsert);
    }
    else if (*toInsert > *root->data)
    {
        insertHelper(root->right, toInsert);
    }
    else
    {
        return false;
    }

    return true;
}

// --------------------- retrieve -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::retrieve(const NodeData &toRetrieve, NodeData* &retrieved)
{
    return retrieveHelper(this->root,toRetrieve, retrieved);
}

bool BinTree::retrieveHelper(Node* &current, const NodeData &toRetrieve, NodeData* &retrieved) const
{
    if (current == NULL)
    {
        toRetrieve = NULL;
        return false;
    }

    if (*current->data == toRetrieve)
    {
        retrieved = current->data;
        return true;
    }
    else if (current->data < toRetrieve)
    {
        retrieveHelper(current->left, toRetrieve, retrieved);
    }
    else if (current->data > toRetrieve)
    {
        retrieveHelper(current->right, toRetrieve, retrieved);
    }
    else
    {
        return false;
    }
}

// --------------------- displaySideways -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::displaySideways() const
{
    sideways(root, 0);  // get her comments
}

// --------------------- inorderHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::inorderHelper(Node* traversal) const
{
    if (traversal != NULL)
    {
        inorderHelper(traversal->left);
        cout << *traversal->data << " ";
        inorderHelper(traversal->right);
    }
}

// --------------------- sideways -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const
{
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}

// --------------------- getHeight -----------------------------------------
//
// --------------------------------------------------------------
int BinTree::getHeight(const NodeData &toFind) const
{
    if (this->root == NULL)
    {
        return 0;
    }

    Node* target = NULL;
    int currentHeight = 0;
    int foundHeight = getHeightHelper(toFind, this->root, currentHeight, target);

    if (foundHeight == -1)
    {
        return 0;
    }
    else
    {
        int maxLeafHeight = foundHeight;

        maxLeafHeight = findLeafHeightHelper(target, foundHeight);

        return maxLeafHeight - foundHeight + 1;
    }

}

// --------------------- getHeightHelper -----------------------------------------
//
// --------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData &toFind, Node* current, int currentHeight, Node* &target) const
{
    if (current == NULL)
    {
        target = NULL;
        return -1;
    }

    if (*current->data == toFind)
    {
        target = current;
        return currentHeight;
    }
    else
    {
        int leftHeight = getHeightHelper(toFind, current->left, currentHeight + 1, target);

        if (leftHeight != 1)
        {
            return leftHeight;
        }

        int rightHeight = getHeightHelper(toFind, current->right, currentHeight + 1, target);

        if (rightHeight != 1)
        {
            return rightHeight;
        }

        target = NULL;

        return -1;
    }
}

// --------------------- findLeafHeightHelper -----------------------------------------
//
// --------------------------------------------------------------
int BinTree::findLeafHeightHelper(const Node* current, int currentHeight) const
{
    int leftLeafHeight = 0;
    int rightLeafHeight = 0;

    if (current->left == NULL && current->right == NULL)
    {
        return currentHeight;
    }
    else
    {
        if (current->left != NULL)
        {
            leftLeafHeight = findLeafHeightHelper(current->left, currentHeight + 1);
        }

        if (current->right != NULL)
        {
            rightLeafHeight = findLeafHeightHelper(current->right, currentHeight + 1);
        }

        if (leftLeafHeight > rightLeafHeight)
        {
            return leftLeafHeight;
        }
        else
        {
            return rightLeafHeight;
        }
    }
}

// --------------------- bstreeToArrayHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arrayToFill[])
{
    int index = 0;

    bstreeToArrayHelper(this->root, arrayToFill, index);
}

// --------------------- getHeightHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::bstreeToArrayHelper(Node* current, NodeData* arrayToFill[], int &index)
{
    if (current == NULL)
    {
        return;
    }

    bstreeToArrayHelper(current->left, arrayToFill, index);
    arrayToFill[index] = current->data;
    index++;
    bstreeToArrayHelper(current->right, arrayToFill, index);
}

// --------------------- arrayToBSTree -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* sourceArray[])
{
    int end = 0;

    for(int i = 0; i < 100; i++) //Count how many indexs of array are used
    {
        if (sourceArray[i] != NULL)
            end++;
        else
            sourceArray[i] = NULL;
    }

    //Recursively call helper function to perform calculations
    arrayToBSTreeHelper(root, sourceArray, 0, end-1);
}

// --------------------- arrayToBSTreeHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node *current, NodeData* sourceArray[], int first, int end)
{
    if (sourceArray == NULL)
    {
        return;
    }
    else
    {
        for
    }
}
