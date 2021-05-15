/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: Chengheng Li Chen
 *
 * Created on 6 de matempo de 2021, 20:37
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include "math.h"
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"

template <class K, class V>
class AVLTree : public BinarySearchTree<K, V> {
public:
    AVLTree();
    AVLTree(const AVLTree& orig);
    //virtual ~AVLTree();
    virtual BinaryTreeNode<K, V>* add(const K& k, const V& value);
private:
    int node_height(BinaryTreeNode<K, V>* newNode) const;
    void insertar(BinaryTreeNode<K, V>*& newNode, BinaryTreeNode<K, V>* n);
    void comprovar(BinaryTreeNode<K, V>* node, K key);
    void rightRotate(BinaryTreeNode<K, V>* n);
    void leftRotate(BinaryTreeNode<K, V>* n);
};

/**
 * Constructor AVLTree
 */
template<class K, class V>
AVLTree<K, V>::AVLTree() {
}

/**
 * Constructor copia AVLTree
 * @param orig original
 */
template<class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree& orig) {
}

/**
 * Funcion que comprueba si hace falta rotar
 * 
 * Cost O(1)
 * 
 * @param node nodo a comprovar
 * @param key key del nodo nuevo
 */
template<class K, class V>
void AVLTree<K, V>::comprovar(BinaryTreeNode<K, V>* node, K key) {
    //
    if ((node_height(node->getRight()) - node_height(node->getLeft()) > 1)) {
        if (key > node->getRight()->getKey()) {
            leftRotate(node);
        } else {
            rightRotate(node->getRight());
            leftRotate(node);
        }
    } else

        if (node_height(node->getLeft()) - node_height(node->getRight()) > 1) {
        if (key < node->getLeft()->getKey()) {
            rightRotate(node);
        } else {

            leftRotate(node->getLeft());
            rightRotate(node);
        }

    }
    node->setHeight(1 + max(node_height(node->getRight()), node_height(node->getLeft())));
}

/**
 * Rotacio cap a la dreta, solament fa conexions y assignacions de cost O(1)
 * 
 * Cost O(1)
 * 
 * @param n node a rotar
 */
template<class K, class V>
void AVLTree<K, V>::rightRotate(BinaryTreeNode<K, V>* n) {
    //Hace todas las conexiones de una rotación hacia la derecha
    BinaryTreeNode<K, V>* temp = n->getLeft();
    n->setLeft(temp->getRight());
    if (temp->getRight() != nullptr) {
        temp->getRight()->setPare(n);
    }
    temp->setPare(n->getPare());
    if (n->getPare() == nullptr) {
        this->p_root = temp;
    } else if (n == n->getPare()->getRight()) {
        n->getPare()->setRight(temp);
    } else {

        n->getPare()->setLeft(temp);
    }
    temp->setRight(n);
    n->setPare(temp);

    // update the balance factor
    n->setHeight(1 + max(node_height(n->getRight()), node_height(n->getLeft())));
    temp->setHeight(1 + max(node_height(temp->getRight()), node_height(temp->getLeft())));
}

/**
 * Rotacio cap a l'esquerra, solament fa conexions y assignacions de cost O(1)
 * 
 * Cost O(1)
 * 
 * @param n node a rotar
 */
template<class K, class V>
void AVLTree<K, V>::leftRotate(BinaryTreeNode<K, V>* n) {
    //Hace todas las conexiones de una rotación hacia la izquierda.
    BinaryTreeNode<K, V>* temp = n->getRight();
    n->setRight(temp->getLeft());
    if (temp->getLeft() != nullptr) {
        temp->getLeft()->setPare(n);
    }
    temp->setPare(n->getPare());
    if (n->getPare() == nullptr) {
        this->p_root = temp;
    } else if (n == n->getPare()->getLeft()) {
        n->getPare()->setLeft(temp);
    } else {

        n->getPare()->setRight(temp);
    }
    temp->setLeft(n);
    n->setPare(temp);

    // update the balance factor
    n->setHeight(1 + max(node_height(n->getRight()), node_height(n->getLeft())));
    temp->setHeight(1 + max(node_height(temp->getRight()), node_height(temp->getLeft())));
}

/**
 * 
 * Añade un nodo al árbol 
 * 
 * O(log(n))
 * 
 * @param k key del nodo
 * @param value valor del nodo
 */
template<class K, class V>
BinaryTreeNode<K, V>* AVLTree<K, V>::add(const K& k, const V& value) {
    //Si esta vacío ponemos el root
    if (this->isEmpty()) {
        BinaryTreeNode<K, V> *newNode = new BinaryTreeNode<K, V>(k);
        newNode->addValue(value);
        this->p_root = newNode;
        return this->p_root;
    } 
    //Si no esta vacío llamamos a la función auxiliar
    else {
        BinaryTreeNode<K, V> *newNode = new BinaryTreeNode<K, V>(k);
        newNode->addValue(value);
        insertar(newNode, this->p_root);
        return newNode;
    }
}

/**
 * Función auxiliar recursivo para insertar un nodo
 * 
 * @param newNode nodo a insertar
 * @param n nodo para la recursión
 */
template<class K, class V>
void AVLTree<K, V>::insertar(BinaryTreeNode<K, V>*& newNode, BinaryTreeNode<K, V>* n) {
    //Si el key es mayor a nos vamos a la derecha
    if (newNode->getKey() > n->getKey()) {
        if (n->hasRight()) {
            insertar(newNode, n->getRight());
        } else {
            //Si no hay derecha añadimos el nodo en ese sitio
            newNode->setPare(n);
            n->setRight(newNode);
        }
    //Si tiene el mismo key se añade el valor al vector del key
    } else if (newNode->getKey() == n->getKey()) {
        n->addValue(newNode->getValues()[0]);
        //Se elimina el nodo
        delete newNode;
        //Se asigna el valor para el return
        newNode = n;
    //Si el key es menor nos vamos a la izquierda
    } else {
        if (n->hasLeft()) {
            insertar(newNode, n->getLeft());
        } else {
            //Si no hay izquierda añadimos nodo
            newNode->setPare(n);
            n->setLeft(newNode);
        }
    }
    //comprueba si hace falta balancear
    comprovar(n, newNode->getKey());
}

/**
 * Métode auxiliar per a calcular l'alçada/ factor de balanç.
 * 
 * @param newNode
 * @return factor de balance del nodo
 */
template<class K, class V>
int AVLTree<K, V>::node_height(BinaryTreeNode<K, V>* newNode) const {
    if (newNode == nullptr)
        return -1;
    else
        return newNode->getHeight();
}

#endif /* AVLTREE_H */
