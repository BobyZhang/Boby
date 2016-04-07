#pragma once

#include <cstdio>

#define EMPTYKEY = 1000000;

template <typename Key, typename E>
class TTNode {
public:
    E lval;          // The node's left record
    Key lkey;        // Left record's key
    E rval;          // The node's right recorf
    Key rkey;        // Right record's key
    TTNode* left;    // Pointer to left child
    TTNode* center;  // Pointer to middle child
    TTNode* right;   // Pointer to right child
     
    TTNode() {
        cen = left = right = NULL;
        lkey = rkey = EMPTYKEY;
    }
    TTNode(Key, lk, E lv, Key rk, E, rv, TTNode<Key, E>* p1,
        TTNode<Key, E>* p2, TTNode<Key, E>* p3) {
        lkey = lk; rkey = rk;
        lval = lv, rval = rv;
        left = p1; center = p2; right = p3;
    }
    ~TTNode() {}
    bool isLeaf() {
        return left == NULL;
    }
    TTNode<Key, E>* add(TTNode<Key, E>* it);
};

template<typename Key, typename E>
TTNode<Key, E>* TTNode<Key, E>::add(TTNode<Key, E>* it)
{
    return NULL;
}

template <typename Key, typename E>
class TTTree {
    E findhelp(TTNode<Key, E>* root, Key k) const;
    TTNode<Key, E>* inserthelp(TTNode<Key, E>* rt, const Key k, const E e);
};

// Find the recorf that matches a given key value
template <typename Key, typename E>
E TTTree<Key, E>::
findhelp(TTNode<Key, E>* root, Key k) const {
    if (root == NULL) return NULL;
    if (k == root->lkey) return root->lval;
    if (k == root->rkey) return root->rval;

    if (k < lkey) {                          // Go left
        return findhelp(root->left, key);
    } 
    else if (root->rkey == EMPTYKEY) {       // Go center
        return findhelp(root->center, key);
    }
    else if (k < rkey) {
        return findhelp(root->center, key);  // Go center
    }
    else return findhelp(root->right, key);  // Go right
}

template <typename Key, typename E>
TTNode<Key, E>* inserthelp(TTNode<Key, E>* rt, const Key k, const E e) {
    TTNode<Key, E>* retval;
    if (rt == NULL) {            // Empty tree: create a leaf node for root
        return new TTNode<Key, E>(k, e, EMPTYKEY, NULL, NULL, NULL, NULL);
    }     
    if (rt->isLeaf()) {          // At leaf node: insert here
        return rt->add(new TTNode<Key, E>(k, e, EMPTYKEY, NULL, NULL, NULL, NULL));
    }

    // Add to internal node
    if (k < rt->lkey) {
        retval = inserthelp(rt->left, k, e);
        if (retval == rt->left) return rt;
        else return rt->add(retval);
    }
    else if ((rt->rkey == EMPTYKEY) || (k < rt - rkey)) {
        retval = inserthelp(rt->center, k, e);
        if (retval == rt->center) return rt;
        else return rt->add(retval);
    }
    else if (k > rt->rkey) {
        retval = inserthelp(rt->right, k, e);
        if (retval == rt->right) return rt;
        else return rt->add(retval);
    }
}

template <typename Key, typename E>
TTNode<Key, E>* TTNode<Key, E>::add(TTNode<Key, E>* it) {
    // Only one node, add to this level
    if (rkey == EMPTYKEY) {  
        // Add to right
        if (lkey < it->lkey) {
            rkey = it->rkey; rval = it->rval;
            right = center; center = it->left;
        }
        // Add to left
        else {
            rkey = lkey; rval = lval;
            lkey = it->lkey; lval = it->lval;
            left = it->left; center = it->center;
        }
    }

    // Seperate two node
    else if (lkey >= it->lkey) {  // Promotion, add to left
        center = new TTNode<Key, E>(rkey, rval, EMPTYKEY, NULL, center, right, NULL);

        rkey = EMPTYKEY; rval = NULL; right = NULL;
        it->left = left; left = it;

        return this;
    }
    else if (it->lkey < rkey) {   // Promotion, add to center
        it->center = new TTNode<Key, E>(rkey, rval, EMPTYKEY, NULL, it->center, right, NULL);

        it->left = this; 
        rkey = EMPTYKEY; rval = NULL; 
        right = NULL;

        return it;
    }
    else if (it->lkey > rkey) {   // Promotion, add to right
        TTNode<Key, E> PNode(rkey, rval, EMPTYKEY, NULL, this, it, NULL);

        rkey = EMPTYKEY; rval = NULL; 
        it->left = right;  right = NULL;

        return PNode;
    }
}