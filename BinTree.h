//
// Created by Shyawn Karim on 10/13/15.
//

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H


#include "nodedata.h"

class BinTree
{
    friend std::ostream& operator<<(std::ostream &outStream, const BinTree &);
//    friend std::istream& operator>>(std::istream &inStream, BinTree &);
			// you add class/method comments and assumptions
public:
    BinTree();								// constructor
    BinTree(const BinTree &);				// copy constructor
    ~BinTree();								// destructor, calls makeEmpty

    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true

    BinTree& operator=(const BinTree &);

    bool operator==(const BinTree &) const;
    bool operator!=(const BinTree &) const;

    bool insert(NodeData*);

    bool retrieve(const NodeData &, NodeData* &);
    void displaySideways() const;			// provided below, displays the tree sideways

    int getHeight(const NodeData &) const;

private:
    struct Node
    {
        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root;								// root of the tree

    // utility functions
    void inorderHelper(Node*) const;
    void sideways(Node*, int) const;	// provided below, helper for displaySideways()
    void makeEmptyHelper(Node* current);
    bool insertHelper(Node*&, NodeData*);
    void assignmentHelper(Node*);
    bool retrieveHelper(Node* &, const NodeData &, NodeData* &) const;
    bool equalityComparisonHelper(Node*, Node*) const;
    int getHeightHelper(const NodeData &, Node*, int, Node* &) const;
    int findLeafHeightHelper(const Node*, int) const;
};


#endif //BINTREE_BINTREE_H
