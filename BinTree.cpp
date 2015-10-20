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

// --------------------- Constructor -----------------------------------------
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
bool BinTree::operator==(const BinTree &tree) const
{
    return false;
}

// --------------------- Overloaded != -----------------------------------------
//
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree &tree) const
{
    return false;
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
bool BinTree::retrieve(const NodeData &toRetrieve, NodeData* &retrieved) const
{
    return retrieveHelper(toRetrieve);
}

bool BinTree::retrieveHelper(const Node*) const
{

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
