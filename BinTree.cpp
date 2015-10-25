// --------------------- BinTree.cpp -----------------------------------------
//
// Shyawn Karim, CSS 343
// Created:         October 13, 2015
// Last Modified:   October 24, 2015
// --------------------------------------------------------------
// Purpose: Creates a binary search tree class called BinTree
// along with functions that allow for tree building, tree modifing,
// and tree destroying.
// --------------------------------------------------------------
// Assumptions: All data is assumed to be correct and all of the
// BSTs are assumed to be 100 nodes or less.
// --------------------------------------------------------------

#include "bintree.h"

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
void BinTree::inorderHelper(Node* current) const
{
    if (current != NULL)  // traverse and print data
    {
        inorderHelper(current->left);
        cout << *current->data << " ";
        inorderHelper(current->right);
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
    this->root = NULL;
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
        makeEmptyHelper(current->left); // left
        makeEmptyHelper(current->right);    // right

        if (current->data != NULL)
        {
            delete current->data;   // deletes the data
            current->data = NULL;
        }

        delete current; // sets pointer to NULL
        current = NULL;
    }
}

// --------------------- Overloaded = -----------------------------------------
// Makes the left tree a deep copy of the right tree
// Uses helper function assignmentHelper to traverse the tree
// --------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rTree)
{
    if (*this == rTree) // check if both trees are the same
    {
        return *this;
    }

    this->makeEmpty();  // deletes the left tree

    assignmentHelper(rTree.root, this->root);

    return *this;   // returns lTree when its the same as rTree
}

// --------------------- assignmentHelper -----------------------------------------
// Helper function to overloaded assignment operator
// --------------------------------------------------------------
void BinTree::assignmentHelper(Node* rTree, Node* &lTree)
{
    if (rTree != NULL) // preorder traverse right tree
    {

        lTree = new Node;   // new node for left tree
        NodeData *temp = new NodeData(*rTree->data);    //copies rTree NodeData to temp
        lTree->data = temp; // set left tree data to temp

        assignmentHelper(rTree->left, lTree->left); // left
        assignmentHelper(rTree->right, lTree->right);   //right
    }
    else
    {
        lTree = NULL;  // copy empty tree
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
        current = new Node;   // new node created
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
// Returns the height of a given node in a binary standard tree
// If the node given is a leaf than the height is 1
// Uses helper function getHeightHelper
// --------------------------------------------------------------
int BinTree::getHeight(const NodeData &toFind) const
{
    return getHeightHelper(toFind, this->root);
}

// --------------------- getHeightHelper -----------------------------------------
// Helper function to getHeight
// Finds the specific node in the tree, if it exists
// Uses helper function recursiveGetHeightHelper
// --------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData &toFind, Node* current) const
{
    if (current == NULL)
    {
        return 0;   // node is not in tree, return height = 0
    }
    else if (*current->data == toFind)
    {
        return recursiveGetHeightHelper(current);   // node found
    }
    else
    {
        int left = getHeightHelper(toFind, current->left);  // search left
        int right = getHeightHelper(toFind, current->right);    // search right

        return max(left, right);
    }
}

// --------------------- secondGetHeightHelper -----------------------------------------
// Helper function to getHeightHelper
// Determines the height of the root node
// --------------------------------------------------------------
int BinTree::recursiveGetHeightHelper(Node* current) const
{
    if (current == NULL)
    {
        return 0;   // have reached a leaf node
    }
    else
    {
        // counts the amount of levels in the tree from root node
        return 1 + max(recursiveGetHeightHelper(current->left), recursiveGetHeightHelper(current->right));
    }
}

// --------------------- bstreeToArrayHelper -----------------------------------------
// Transfers all of the nodes from a BST into an array and then deletes the BST
// Uses helper function bstreeToArrayHelper
// --------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* arrayToFill[])
{
    bstreeToArrayHelper(this->root, arrayToFill);

    this->makeEmpty();  // delete the BST
}

// --------------------- bstreeToArrayHelper -----------------------------------------
// Helper function to bstreeToArrayHelper
// --------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* current, NodeData* arrayToFill[])
{
    if (current == NULL)
    {
        return 0;   // end of BST
    }

    int left = bstreeToArrayHelper(current->left, arrayToFill);

    NodeData *temp;
    temp = current->data; // saves NodeData to temp
    current->data = NULL; // current no longer points to node
    *(arrayToFill + left) = temp; //arrayToFill points to temp
    temp = NULL;

    int right = bstreeToArrayHelper(current->right, arrayToFill + left + 1);

    return left + right + 1; // return position
}

// --------------------- arrayToBSTree -----------------------------------------
// Builds a balanced BST from a sorted array of NodeData
// Array is filled with NULLs at the end
// Uses helper function arrayToBSTreeHelper
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* sourceArray[])
{
    this->makeEmpty();  // delets current BST

    int high = 0;

    for(int i = 0; i < 100; i++)    // assumed to be no more than 100 elements
    {
        if (sourceArray[i] != NULL)
        {
            high++; // find how many elements points to NodeData
        }
        else
        {
            sourceArray[i] = NULL;
        }
    }

    arrayToBSTreeHelper(root, sourceArray, 0, high-1);
}

// --------------------- arrayToBSTreeHelper -----------------------------------------
// Helper function to arrayToBSTree
// Builds BST and sets array to NULL
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node *current, NodeData* sourceArray[], int low, int high)
{
    if (low > high)
    {
        current = NULL; // end of array NodeData
    }
    else
    {
        int mid = (low + high) / 2; // picks NodeData from array to build balanced tree

        NodeData* temp; // temp NodeData pointer
        temp = sourceArray[mid];    // assigns mid element from array section to temp
        sourceArray[mid] = NULL;    // sets that array element to NULL

        insert(temp);   // inserts NodeData int BST
        arrayToBSTreeHelper(current, sourceArray, low, mid - 1);    // fill left
        arrayToBSTreeHelper(current, sourceArray, mid + 1, high);   // fill right
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