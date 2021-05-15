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

/**
 * Constructor de BinaryTreeNode
 * @param _key key del nodo
 */
template <class K, class V>
BinaryTreeNode<K, V>::BinaryTreeNode(const K& _key) {
    key = _key;
    pare = nullptr;
    left = nullptr;
    right = nullptr;
    _height = 0;
}

/**
 * Constructor cópia
 * 
 * @param orig nodo original
 */
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

/**
 * Destructor
 */
template <class K, class V>
BinaryTreeNode<K, V>::~BinaryTreeNode() {
    if (right != nullptr)
        delete right;
    if (left != nullptr)
        delete left;
}
/**
 * Añade un valor
 * @param v valor a añadir
 */
template<class K, class V>
void BinaryTreeNode<K, V>::addValue(const V& v) {
    this->values.push_back(v);
}
/**
 * Getter del key
 * @return 
 */
template<class K, class V>
const K& BinaryTreeNode<K, V>::getKey() const {
    return key;
}
/**
 * Getter de los valores
 * @return vector de valores
 */
template<class K, class V>
const vector<V>& BinaryTreeNode<K, V>::getValues() const {
    return this->values;
}
/**
 * Profundidad del nodo
 * @return profundidad
 */
template<class K, class V>
int BinaryTreeNode<K, V>::depth() const {
    if (isRoot())
        return 0;
    else {
        return 1 + pare->depth();
    }
}
/**
 * Comprueba si tiene hijo derecho
 * @return true si tiene, false si no tiene
 */
template<class K, class V>
bool BinaryTreeNode<K, V>::hasLeft() const {
    return !(this->left == nullptr);
}
/**
 * Comprueba si tiene hijo izquierdo
 * @return true si tiene, false si no tiene
 */
template<class K, class V>
bool BinaryTreeNode<K, V>::hasRight() const {
    return !(this->right == nullptr);
}
/**
 * Comprueba si es una hoja
 * @return true si tiene, false si no tiene
 */
template<class K, class V>
bool BinaryTreeNode<K, V>::isLeaf() const {
    return (!(hasRight() or hasLeft()));
}
/**
 * Comprueba si es el root
 * @return true si tiene, false si no tiene
 */
template<class K, class V>
bool BinaryTreeNode<K, V>::isRoot() const {
    return (this->pare == nullptr);
}
/**
 * Calcula la altura del nodo
 * @return altrura
 */
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
/**
 * modificacion del operador ==
 * @param node nodo a comparar
 * @return si son iguales
 */
template<class K, class V>
bool BinaryTreeNode<K, V>::operator==(const BinaryTreeNode<K, V>& node) const {
    return (values == node.getValues() and key == node.getKey());
}
/**
 * Devuelve el nodo izquierdo
 * @return nodo izq
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getLeft() {
    return left;
}
/**
 * Devuelve el nodo padre
 * @return nodo padre
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getPare() {
    return pare;
}
/**
 * Devueve el nodo derecho
 * @return nodo der
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinaryTreeNode<K, V>::getRight() {
    return right;
}
/**
 * Setter del nodo izq
 * @param _left nodo izq
 */
template<class K, class V>
void BinaryTreeNode<K, V>::setLeft(BinaryTreeNode<K, V>* _left) {
    left = _left;
}
/**
 * Setter del nodo padre
 * @param _pare nodo padre
 */
template<class K, class V>
void BinaryTreeNode<K, V>::setPare(BinaryTreeNode<K, V>* _pare) {
    pare = _pare;
}
/**
 * Setter del nodo derecha
 * @param _right nodo der
 */
template<class K, class V>
void BinaryTreeNode<K, V>::setRight(BinaryTreeNode<K, V>* _right) {
    right = _right;
}
/**
 * Setter del Heigth/Factor de balance
 * @param n factor de balance
 */
template <class K, class V>
void BinaryTreeNode<K, V>::setHeight(int n) {
    _height = n;
}
/**
 * Getter del height/factor de balance
 * @return factor del balance
 */
template <class K, class V>
int BinaryTreeNode<K, V>::getHeight() const{
    return _height;
}

#endif /* BINARYTREENODE_H */

