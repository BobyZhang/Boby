

#pragma once

#include "linklist.h"

// Binary tree node abstract class
template <typename E>
class BinNode {
public:
	virtual ~BinNode() {}

	// return the node's value
	virtual E& element() = 0;

	// set node's value
	virtual void setElement(const E&) = 0;
	
	// return the node's child
	virtual BinNode* left() const = 0;
	virtual BinNode* right() const = 0;

	// set the node's child
	virtual void setLeft(BinNode*) = 0;
	virtual void setRight(BinNode*) = 0;

	// return true if the node if a leaf, false otherwise
	virtual bool isLeaf() = 0;
};

// simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
	Key k;
	E it;
	BSTNode* lc;   // pointer to left child
	BSTNode* rc;   // pointer to right child

public:
	BSTNode() { lc = rc = NULL; }
	BSTNode(Key k, E e, BSTNode* l = NULL, BSTNode* r = NULL) 
	{ k = K; it = e; lc = l; rc = r; }
	~BSTNode() {}

	// function to set and return the value and key
	E& element() { return it; }
	void setElement(const E& e) { it = e; }
	Key& key() { return k; }
	void setKey(const Key& K) { k = K; }

	// function to set and return the children
	inline BSTNode* left() const { return lc; }
	void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
	inline BSTNode* rigth() const { return rc; }
	void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }

	// whether leaf node
	bool isLeaf() { return (lc = NULL) && (rc = NULL); }
};