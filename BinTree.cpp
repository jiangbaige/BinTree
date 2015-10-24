// --------------------- BinTree.cpp -----------------------------------------
//
// Shyawn Karim, CSS 343
// Created:         October 13, 2015
// Last Modified:   October 24, 2015
// --------------------------------------------------------------
// Purpose: This class implements a representation of polynomials
// that do not have negative exponents.  Each polynomial is
// stored completely in one array. The index of the array
// represents the power and is where the corresponding coefficient
// is stored. Polynomials will be able to be changed any time and
// can be added, subtracted, or multiplied by each other.
// --------------------------------------------------------------
// Assumptions: All data will be assumed to be correct and there
// is no error handling of any kind.  Negative exponents will be
// ignored.
// --------------------------------------------------------------

#include "BinTree.h"

using namespace std;


// --------------------- Overloaded << -----------------------------------------
// Displays data from the BSTree in order.
// Uses helper function inorderHelper to traverse tree
// --------------------------------------------------------------
ostream &operator<<(ostream &outStream, const BinTree &tree)
{
    tree.inorderHelper(tree.root);
    outStream << endl;
    return outStream;
}

// --------------------- inorderHelper -----------------------------------------
// Helper function for overloaded operator <<
// --------------------------------------------------------------
void BinTree::inorderHelper(Node* traversal) const
{
    if (traversal != NULL)  // traverse and print data
    {
        inorderHelper(traversal->left);
        cout << *traversal->data << " ";
        inorderHelper(traversal->right);
    }
}

// --------------------- Default Constructor -----------------------------------------
// Creates an empty BSTree with the root set to NULL
// --------------------------------------------------------------
BinTree::BinTree()
{
    this->root = NULL;
}

// --------------------- Copy Constructor -----------------------------------------
// Creates a deep copy of a referenced BSTree passed in
// --------------------------------------------------------------
BinTree::BinTree(const BinTree &sourceTree)
{
    this->root = NULL; // maybe not needed
    *this = sourceTree;
}

// --------------------- Destructor -----------------------------------------
// Calls makeEmpty to delete a BSTree
// --------------------------------------------------------------
BinTree::~BinTree()
{
    this->makeEmpty();
}

// --------------------- isEmpty -----------------------------------------
// Checks whether a BSTree is empty or not
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
// Deletes and entire BSTree
// Uses helper function makeEmptyHelpter
// --------------------------------------------------------------
void BinTree::makeEmpty()
{
        makeEmptyHelper(root);
}

// --------------------- makeEmptyHelper -----------------------------------------
// Helper function for makeEmpty
// --------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*& current)
{
    if (current != NULL)    // post order traversal
    {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);

        current->data = NULL;
        delete current->data;   // delete NodeData
        current = NULL;
        delete current; // delete node

    }
}

// --------------------- Overloaded = -----------------------------------------
// Makes the left tree a deep copy of the right tree
// Uses helper function assignmentHelper to traverse the tree
// --------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rTree)
{
    if (*this == rTree)
    {
        return *this;
    }

    this->makeEmpty();  // deletes the left tree

    this->assignmentHelper(rTree.root);

    return *this;
}

// --------------------- assignmentHelper -----------------------------------------
// Helper function to overloaded assignment operator
// --------------------------------------------------------------
void BinTree::assignmentHelper(Node* current)
{
    if (current != NULL)    // preorder traverse right tree
    {
        insert(current->data);  // insert node in left tree
        assignmentHelper(current->left);
        assignmentHelper(current->right);
    }
}

// --------------------- Overloaded == -----------------------------------------
// Checks if two BSTrees are exactly the same
// Uses helper function equalityComparisonHelper
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
// Helper function to overloaded operator ==
// --------------------------------------------------------------
bool BinTree::equalityComparisonHelper(Node* lNode, Node* rNode) const
{
    if (lNode == NULL && rNode == NULL)
    {
        return true;    // tree if both nodes are NULL
    }

    if (lNode == NULL || rNode == NULL)
    {
        return false;   // false if one node has data and the other does not
    }

    if (*lNode->data == *rNode->data
        && lNode->left == NULL && rNode->left == NULL
        && lNode->right == NULL && rNode->right == NULL)
    {
        return true;    // true if nodes being compared have the same data and no children
    }

    // both nodes contain the same NodeData
    // continue to traverse both trees
    return (*lNode->data == *rNode->data
           && equalityComparisonHelper(lNode->left, rNode->left)
           && equalityComparisonHelper(lNode->right, rNode->right));
}

// --------------------- Overloaded != -----------------------------------------
// Checks if two BSTrees are not exactly the same
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rTree) const
{
    return !(*this == rTree);
}

// --------------------- insert -----------------------------------------
// Inserts a new node containing NodeData into a BSTree
// Uses helper function insertHelper
// --------------------------------------------------------------
bool BinTree::insert(NodeData* toInsert)
{
    return insertHelper(this->root, toInsert);
}

// --------------------- insertHelper -----------------------------------------
// Helper function to insert
// If NodeData is already in BSTree then node is not inserted
// --------------------------------------------------------------
bool BinTree::insertHelper(Node*& current, NodeData* toInsert)
{
    if (current == NULL)    // insert new node here
    {
        current = new Node();   // new node created
        current->data = toInsert;   // NodeData set to node
        current->left = NULL;   // left child set to NULL
        current->right = NULL;  // right child set to NULL
    }
    else if (*toInsert < *current->data)
    {
        insertHelper(current->left, toInsert);  // traverse left
    }
    else if (*toInsert > *current->data)
    {
        insertHelper(current->right, toInsert); // traverse right
    }
    else
    {
        return false;   // node already exists and is not inserted
    }

    return true;    // node inserted
}

// --------------------- retrieve -----------------------------------------
// Checks whether or not a NodeData is in a BSTree
// If found returns a pointer to that node
// Uses helper function retrieveHelper
// --------------------------------------------------------------
bool BinTree::retrieve(const NodeData &toRetrieve, NodeData* &retrieved)
{
    retrieveHelper(this->root,toRetrieve, retrieved);   // search tree

    if (retrieved != NULL)
    {
        return true;    // NodeData found
    }

    return false;   // NodeData not in tree
}

// --------------------- retrieveHelper -----------------------------------------
// Helper function to retrieve
// --------------------------------------------------------------
bool BinTree::retrieveHelper(Node* &current, const NodeData &toRetrieve, NodeData* &retrieved) const
{
    if (current == NULL)    // NodeData is not found
    {
        retrieved = NULL;   // return pointer set to NULL
        return false;
    }

    if (*current->data == toRetrieve)   // NodeData found
    {
        retrieved = current->data;  // return pointer set to NodeData
        return true;
    }
    else if (*current->data < toRetrieve)
    {
        retrieveHelper(current->right, toRetrieve, retrieved);  // traverse right
    }
    else if (*current->data > toRetrieve)
    {
        retrieveHelper(current->left, toRetrieve, retrieved);   // traverse left
    }
    else
    {
        return false;   // NodeData not found
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
    // int index = 0;

    bstreeToArrayHelper(this->root, arrayToFill);

    this->makeEmpty();
}

// --------------------- bstreeToArrayHelper -----------------------------------------
//
// --------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* current, NodeData* arrayToFill[])
{
    if (current == NULL)
    {
        return 0;
    }

    int left = bstreeToArrayHelper(current->left, arrayToFill);

    NodeData *temp;
    temp = current->data; // save the pointer to NodeData object to temp
    current->data = NULL; // disconnect NodeData from Node
    *(arrayToFill + left) = temp; //arrayToFill points to temp
    temp = NULL; // disconnect

    int right = bstreeToArrayHelper(current->right, arrayToFill + left + 1);

    return left + right + 1; //Return position
}

// --------------------- arrayToBSTree -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* sourceArray[])
{
    this->makeEmpty();

    int high = 0;

    for(int i = 0; i < 100; i++) //Count how many indexes of array are used
    {
        if (sourceArray[i] != NULL)
        {
            high++;
        }
        else
        {
            sourceArray[i] = NULL;
        }
    }

    //Recursively call helper function to perform calculations
    arrayToBSTreeHelper(root, sourceArray, 0, high-1);
}

// --------------------- arrayToBSTreeHelper -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node *current, NodeData* sourceArray[], int low, int high)
{
    if (low > high)
    {
        current = NULL;
    }
    else
    {
        int mid = (low + high) / 2;

        NodeData* temp;
        temp = sourceArray[mid];
        sourceArray[mid] = NULL;

        insert(temp);
        arrayToBSTreeHelper(current, sourceArray, low, mid - 1);    // left
        arrayToBSTreeHelper(current, sourceArray, mid + 1, high);   // right
    }
}

// --------------------- displaySideways -----------------------------------------
//
// --------------------------------------------------------------
void BinTree::displaySideways() const
{
    sideways(root, 0);  // get her comments
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