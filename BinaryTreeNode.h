/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTreeNode.h
 * Author: li471
 *
 * Created on 20 de abril de 2021, 11:43
 */

#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <vector>
using namespace std;

template <class K, class V>
class BinaryTreeNode {
public:
    BinaryTreeNode(const K& key);
    BinaryTreeNode(const BinaryTreeNode<K, V>& orig);
    virtual ~BinaryTreeNode();

    /* Modificadors */
    // Declareu-hi aquí els modificadors (setters) dels atributs que manquen

    void setPare(BinaryTreeNode<K, V>* _pare);
    void setLeft(BinaryTreeNode<K, V>* _left);
    void setRight(BinaryTreeNode<K, V>* _right);

    /* Consultors */
    const K& getKey() const;
    const vector<V>& getValues() const;

    // Declareu-hi aquí els consultors (getters) dels atributs que manquen
    BinaryTreeNode<K, V>* getPare();
    BinaryTreeNode<K, V>* getRight();
    BinaryTreeNode<K, V>* getLeft();

    /* Operacions */
    bool isRoot() const;
    bool hasLeft() const;
    bool hasRight() const;
    bool isLeaf() const;

    void addValue(const V& v);
    int depth() const;
    int height() const; // uses auxiliary attribute
    bool operator==(const BinaryTreeNode<K, V>& node) const;
    void setHeight(int n);
    int getHeight() const;
private:
    K key;
    vector<V> values;
    BinaryTreeNode<K, V> *pare;
    BinaryTreeNode<K, V> *left;
    BinaryTreeNode<K, V> *right;
    int _height;

};

using namespace std;
#include <vector>
#include <iostream>
#include <ratio>

template <class K, class V>
BinaryTreeNode<K, V>::BinaryTreeNode(const K& _key) {
    key = _key;
    pare = nullptr;
    left = nullptr;
    right = nullptr;
    _height = 0;
}

template <class K, class V>
BinaryTreeNode<K, V>::BinaryTreeNode(const BinaryTreeNode<K, V>& orig) {
    key = orig.key;
    values = orig.values;
    _height = orig._height;
    if (orig.hasRight()) {
        BinaryTreeNode<K, V> *newNode_r = new BinaryTreeNode<K, V>(*orig.right);
        this->setRight(newNode_r);
        newNode_r->setPare(this);
    }
    if (orig.hasLeft()) {
        BinaryTreeNode<K, V> *newNode_l = new BinaryTreeNode<K, V>(*orig.left);
        this->setLeft(newNode_l);
        newNode_l->setPare(this);
    }
}

template <class K, class V>
BinaryTreeNode<K, V>::~BinaryTreeNode() {
    if (right != nullptr)
        delete right;
    if (left != nullptr)
        delete left;
}

template<class K, class V>
void BinaryTreeNode<K, V>::addValue(const V& v) {
    this->values.push_back(v);
}

template<class K, class V>
const K& BinaryTreeNode<K, V>::getKey() const {
    return key;
}

template<class K, class V>
const vector<V>& BinaryTreeNode<K, V>::getValues() const {
    return this->values;
}

template<class K, class V>
int BinaryTreeNode<K, V>::depth() const {
    if (isRoot())
        return 0;
    else {
        return 1 + pare->depth();
    }
}

template<class K, class V>
bool BinaryTreeNode<K, V>::hasLeft() const {
    return !(this->left == nullptr);
}

template<class K, class V>
bool BinaryTreeNode<K, V>::hasRight() const {
    return !(this->right == nullptr);
}

template<class K, class V>
bool BinaryTreeNode<K, V>::isLeaf() const {
    return (!(hasRight() or hasLeft()));
}

template<class K, class V>
bool BinaryTreeNode<K, V>::isRoot() const {
    return (this->pare == nullptr);
}

template<class K, class V>
int BinaryTreeNode<K, V>::height() const {
    int r = 0, l = 0;
    if (this->hasRight())
        r = right->height();
    if (this->hasRight())
        l = left->height();
    if (r > l)
        return r + 1;
    else
        return l + 1;
}

template<class K, class V>
bool BinaryTreeNode<K, V>::operator==(const BinaryTreeNode<K, V>& node) const {
    return (values == node.getValues() and key == node.getKey());
}

template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getLeft() {
    return left;
}

template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getPare() {
    return pare;
}

template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getRight() {
    return right;
}

template<class K, class V>
void BinaryTreeNode<K, V>::setLeft(BinaryTreeNode<K, V>* _left) {
    left = _left;
}

template<class K, class V>
void BinaryTreeNode<K, V>::setPare(BinaryTreeNode<K, V>* _pare) {
    pare = _pare;
}

template<class K, class V>
void BinaryTreeNode<K, V>::setRight(BinaryTreeNode<K, V>* _right) {
    right = _right;
}

template <class K, class V>
void BinaryTreeNode<K, V>::setHeight(int n) {
    _height = n;
}

template <class K, class V>
int BinaryTreeNode<K, V>::getHeight() const{
    return _height;
}

#endif /* BINARYTREENODE_H */

