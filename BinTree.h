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
    bool retrieve(const NodeData &, NodeData* &) const;
    void displaySideways() const;			// provided below, displays the tree sideways

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
    void makeEmptyHelper(Node* current)
};


#endif //BINTREE_BINTREE_H
