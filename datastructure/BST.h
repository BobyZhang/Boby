
#pragma once

#include "linklist.h"
#include "binTree.h"

//
// 
//
template <typename Key, typename E>
int smallcount(BSTNode<Key, E>*, const Key&);

template <typename Key, typename E>
int smallcount(BSTNode<Key, E>* _root, const Key& _k) {
	if (_root == NULL) return 0;
	if (_root->key() <= _k) {
		return 1 + smallcount(_root->left(), _k)
			+ smallcount(_root->right(), _k);
	}
	return 0;
}

// The Dictoinary abstract  class
template <typename Key, typename E>
class Dictionary {
private:
	//void operator ={ const Dictionary& } {}
	Dictionary(const Dictionary&) {}

public:
	Dictionary() {}
	virtual ~Dictionary() {}

	// reinit dictionary
	virtual void clear() = 0;

	// insert a record
	virtual void insert(const Key&, const E&) = 0;

	// remove and return the e, with Key "k" exsits
	virtual E remove(const Key&) = 0;

	// remove and return an arbitrary record
	virtual E removeAny() = 0;

	// return a record matching "k", or NULL if not exsits
	virtual E find(const Key&) const = 0;

	// return the number of records in the dictionary
	virtual int size() = 0;
};

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary < Key, E > {
private:
	BSTNode<Key, E>* root;
	int nodecount;

	// private helper functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,
		const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;
	Key BSTSumhelp(BSTNode<Key, E>* _root) const;

public:
	BST() { root = NULL; nodecount = 0; }
	~BST() { clearhelp(root); }

	void clear() {
		clearhelp(root); root = NULL; nodecount = 0;
	}

	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		++nodecount;
	}

	E remove(const Key& k) {
		E temp = findhelp(root, k);
		if (temp != NULL) {
			root = removehelp(root, k);
			--nodecount;
		}
		return temp;
	}

	E removeAny() {
		if (root != NULL) {
			E temp = root->element();
			root = removehelp(root, root->key());
			--nodecount;
			return temp;
		}
		else return NULL;
	}

	E find(const Key& k) const { return findhelp(root, k); }

	int size() { return nodecount; }

	void print() const {
		if (root == NULL) std::cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}

	Key BSTSum() const {
		return BSTSumhelp(root);
	}

	BSTNode<Key, E>* getroot() const {
		return root;
	}
};

template <typename Key, typename E>
E BST<Key, E>::
findhelp(BSTNode<Key, E>* _root, const Key& _k) const {
	if (_root == NULL) return NULL;
	if (_k < _root->key()) return findhelp(_root->left(), _k);
	else if (_k > _root->key()) return findhelp(_root->right(), _k);
	else return _root->element();
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
inserthelp(BSTNode<Key, E>* _root, const Key& k, const E& it) {
	if (_root == NULL) {
		return new BSTNode<Key, E>(k, it, NULL, NULL);
	}
	if (k < _root->key()) {
		_root->setLeft(inserthelp(_root->left(), k, it));
	}
	else {
		_root->setRight(inserthelp(_root->right(), k, it));
	}
	return _root;
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* _rt) {
	if (_rt->left() == NULL) {
		return _rt->right();
	}
	else {
		_rt->setLeft(deletemin(_rt->left()));
		return _rt;
	}
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* _rt) {
	if (_rt->left() == NULL) return _rt;
	else return getmin(_rt->left());
}

// Remove a node with key value k
// Return : the tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* _rt, const Key& k) {
	if (_rt == NULL) return NULL;
	else if (k < _rt->key()) _rt->setLeft(removehelp(_rt->left(), k));
	else if (k > _rt->key()) _rt->setRight(removehelp(_rt->left(), k));
	else { // when found it, and remove it
		BSTNode<Key, E>* temp = _rt;
		if (_rt->left() == NULL) { // only a right child
			_rt = _rt->right();
			delete temp;
		}
		else if (_rt->right() == NULL) { // only a left child
			_rt = _rt->left();
			delete temp;
		}
		else {  // both childen are noe-empty
			BSTNode<Key, E>* temp = getmin(_rt->right());
			_rt->setElement(temp->element());
			_rt->setKey(temp->key());
			_rt->setRight(deletemin(_rt->right()));
			delete temp;
		}
	}
	return _rt;
}

template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* _root) {
	if (_root == NULL) return;
	clearhelp(_root->left());
	clearhelp(_root->right());
	delete _root;
}

template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* _root, int level) const {
	if (_root == NULL) return;
	printhelp(_root->right(), level + 1);
	for (int i = 0; i < level; ++i) {
		std::cout << "   ";
	}
	std::cout << _root->key() << "\n";
	printhelp(_root->left(), level + 1);
	
}

template <typename Key, typename E>
Key BST<Key, E>::
BSTSumhelp(BSTNode<Key, E>* _root)  const {
	if (_root == NULL) return 0;
	return _root->element()
		+ BSTSumhelp(_root->left())
		+ BSTSumhelp(_root->right());
}

