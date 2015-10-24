// --------------------- BinTree.h -----------------------------------------
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

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H


#include "nodedata.h"

class BinTree
{
    // Overloaded << operator
    friend std::ostream& operator<<(std::ostream &outStream, const BinTree &);

public:
    // Constructors and Destructor
    BinTree();								// constructor
    BinTree(const BinTree &);				// copy constructor
    ~BinTree();								// destructor, calls makeEmpty

    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true

    // Assignment operator
    BinTree& operator=(const BinTree &);

    // Comparison operators
    bool operator==(const BinTree &) const;
    bool operator!=(const BinTree &) const;

    // Inserts a node into a tree
    bool insert(NodeData*);

    // Searches a tree for a particular value
    bool retrieve(const NodeData &, NodeData* &);

    // Returns the height of a particular node in a tree
    int getHeight(const NodeData &) const;

    // Builds an array of NodeData from a BSTree'
    void bstreeToArray(NodeData* []);

    // Builds a BSTree from a NodeData array
    void arrayToBSTree(NodeData* []);

    // Displays the tree sideways
    void displaySideways() const;

private:
    struct Node
    {
        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root;								// root of the tree

    // helper for overloaded <<
    void inorderHelper(Node*) const;

    // helper for makeEmpty
    void makeEmptyHelper(Node*& current);

    // helper for overloaded =
    void assignmentHelper(Node*);

    // helper for overloaded ==
    bool equalityComparisonHelper(Node*, Node*) const;

    // helper for insert
    bool insertHelper(Node*&, NodeData*);

    // helper for retrieve
    bool retrieveHelper(Node* &, const NodeData &, NodeData* &) const;

    // helper for getHeight
    int getHeightHelper(const NodeData &, Node*, int, Node* &) const;

    // helper for the getHeighthelper
    int findLeafHeightHelper(const Node*, int) const;

    // helper for bstreeToArray
    void bstreeToArrayHelper(Node*, NodeData* [], int &);

    // helper for arrayToBSTree
    void arrayToBSTreeHelper(Node*, NodeData* [], int, int);

    // helper for displaySideways
    void sideways(Node*, int) const;//helper for displaySideways()
};


#endif //BINTREE_BINTREE_H
