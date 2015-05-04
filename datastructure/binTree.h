
#pragma once

#include <string>

// Binary tree node abstract class
template <typename E>
class BinNode {
public:
	virtual ~BinNode() {}

	// return the node's value
	virtual E& element() = 0;

	// set the node's value
	virtual void setElement(const E&) = 0;

	// return the node's child
	virtual BinNode* left() = 0;
	virtual BinNode* right() = 0;

	// set the node's child
	virtual void setLeft(BinNode*) = 0;
	virtual void setRight(BinNode*) = 0;

	// return true if the node is a leaf, false otherwise
	virtual bool isLeaf() = 0;
};

// simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode < E > {
private:
	Key k;
	E it;
	BSTNode* lc;
	BSTNode* rc;
public:
	// constructors
	BSTNode() { lc = rc = NULL; }
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL) {
		k = K; it = e; lc = l; rc = r;
	}
	~BSTNode() {}

	// function to set and return the value and key
	E& element() { return it; }
	void setElement(const E& e) { it = e; }
	Key& key() { return k; }
	void setKey(const Key& K) { k = K; }

	// function to set and return the child
	BSTNode* left() { return lc; }
	BSTNode* right() { return rc; }
	void setLeft(BinNode* b) { lc = (BSTNode*)b; }
	void setRight(BinNode* b) { rc = (BSTNode*)b; }

	// whether leaf
	bool isLeaf() { return (lc = NULL) && (rc = NULL); }
};

template <typename Key, typename E>
E binTreeSum(const BSTNode<Key, E>* _node);

template <typename Key, typename E>
E binTreeSum(BSTNode<Key, E>* _node) {
	if (_node == NULL) return 0;
	return (*_node).element()
		+ binTreeSum((*_node).left()) 
		+ binTreeSum((*_node).right());
}