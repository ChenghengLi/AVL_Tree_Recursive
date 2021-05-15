/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearchTree.h
 * Author: li471
 *
 * Created on 20 de abril de 2021, 12:26
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include <string>
#include "BinaryTreeNode.h"
using namespace std;

template <class K, class V>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<K, V>& orig);
    virtual ~BinarySearchTree();

    bool isEmpty() const;
    int size() const;
    int height() const;

    BinaryTreeNode<K, V>* add(const K& k, const V& value);
    bool has(const K& k) const;
    const vector<V>& valuesOf(const K& k) const;

    void showKeysPreorder(BinaryTreeNode<K, V>* n = nullptr) const;
    void showKeysInorder(BinaryTreeNode<K, V>* n = nullptr) const;
    void showKeysPostorder(BinaryTreeNode<K, V>* n = nullptr) const;

    bool equals(const BinarySearchTree<K, V>& other) const;
    vector<BinaryTreeNode<K, V>*> getLeafs();
    //protected:
    BinaryTreeNode<K, V>* p_root;
    BinaryTreeNode<K, V>* find(const K& k) const;
private:
    int _size;
    int max_height(BinaryTreeNode<K, V>* node) const;
    int size_calculator(BinaryTreeNode<K, V> *node) const;
    BinaryTreeNode<K, V>* leave_finder(const K& k, BinaryTreeNode<K, V>* node) const;
    void getLeafs(vector<BinaryTreeNode<K, V>*>& vector, BinaryTreeNode<K, V>* n)const;
    bool equals_1(BinaryTreeNode<K, V>* this_n, BinaryTreeNode<K, V>* other_n)const;
};

#include "BinaryTreeNode.h"
#include <stdexcept>
#include <iostream>
using namespace std;

/**
 * Constructor por defecto
 */
template<class K, class V>
BinarySearchTree<K, V>::BinarySearchTree() {
    p_root = nullptr;
    _size = 0;

}

/**
 * Constructor cópia
 * @param orig orignal
 */
template<class K, class V>
BinarySearchTree<K, V>::BinarySearchTree(const BinarySearchTree<K, V>& orig) {
    p_root = new BinaryTreeNode<V, K>(*orig.p_root);
    _size = orig._size;
}

/**
 * Destructor de la clase
 */
template<class K, class V>
BinarySearchTree<K, V>::~BinarySearchTree() {
    cout << "Destruint l'arbre" << endl;
    delete p_root;
    cout << "..." << endl << "Arbre binari destruit" << endl << endl;
}

/**
 * Añade un nodo
 * 
 * O(h) on h és l'alçada de l'arbre, en el pitjor dels casos serà O(n)
 * 
 * @param k key 
 * @param value valor
 * @return nodo en el que se ha añadido el valor
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinarySearchTree<K, V>::add(const K& k, const V& value) {
    BinaryTreeNode<K, V> *newNode = new BinaryTreeNode<K, V>(k);
    newNode->addValue(value);
    //Si está vacío se lo asigna al root
    if (p_root == nullptr)
        p_root = newNode;
    //Añade el nodo por el medio del árbol
    else {
        BinaryTreeNode<K, V>* temp = p_root;
        bool parar = false;
        while (temp != nullptr and !parar) {
            if (temp->getKey() < k) {
                if (temp->hasRight())
                    temp = temp->getRight();
                else {
                    temp->setRight(newNode);
                    newNode->setPare(temp);
                    _size++;
                }
            } else if (temp->getKey() == k) {
                temp->addValue(value);
                delete newNode;
                newNode = temp;
                parar = true;
            } else {
                if (temp->hasLeft())
                    temp = temp->getLeft();
                else {
                    temp->setLeft(newNode);
                    newNode->setPare(temp);
                    _size++;
                }
            }
        }
    }
    return newNode;
}

/**
 * Retorna si conté un key l'arbre
 * 
 * O(h) on h és l'alçada de l'arbre
 * 
 * @param k
 * @return 
 */
template<class K, class V>
bool BinarySearchTree<K, V>::has(const K& k) const {
    if (leave_finder(k) == nullptr)
        return true;
    else
        return false;
}

/**
 * Busca el nodo donde añadir
 * 
 * O(h) on h és l'alçada de l'arbre
 * 
 * @param k key
 * @param node nodo donde añadir
 * @return nodo donde añadir
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinarySearchTree<K, V>::leave_finder(const K& k, BinaryTreeNode<K, V>* node) const {
    if (node->getKey() > k) {
        if (node->getLeft() == nullptr)
            return node;
        leave_finder(k, node->getLeft());
    } else if (node->getKey() == k)
        return nullptr;
    else {
        if (node->getRight() == nullptr)
            return node;
        leave_finder(k, node->getRight());
    }
}

/**
 * Busca si un nodo con determinado key existe
 * 
 * O(h) donde h es la altura del árbol
 * 
 * @param k key
 * @return el nodo si existe y nullptr si no
 */
template<class K, class V>
BinaryTreeNode<K, V>* BinarySearchTree<K, V>::find(const K& k) const {
    BinaryTreeNode<K, V> *temp = p_root;
    //Bucle while que se mueve a la derecha o a la izquierda dependiendo del key
    while (temp != nullptr and temp->getKey() != k) {
        if (temp->getKey() > k) {
            temp = temp ->getLeft();
        } else {
            temp = temp ->getRight();
        }
    }
    return temp;
}

/**
 * Recoge todos los nodos que son hojas
 * 
 * O(n) 
 * 
 * @return vector con las hojas del árbol
 */
template<class K, class V>
vector<BinaryTreeNode<K, V>*> BinarySearchTree<K, V>::getLeafs() {
    vector<BinaryTreeNode<K, V>*> vector;
    getLeafs(vector, p_root);
    return vector;
}

/**
 * Función auxiliar recursivo para hallar las hojas del árbol
 * 
 * O(n)
 * 
 * @param vector vector donde contiene las hojas
 * @param n nodo recursivo
 */
template<class K, class V>
void BinarySearchTree<K, V>::getLeafs(vector<BinaryTreeNode<K, V>*>& vector, BinaryTreeNode<K, V>* n) const {
    //Si tiene nodo derecha revisa el modo
    if (n->hasLeft()) {
        getLeafs(vector, n->getLeft());
    }
    //Si tiene nodo izquierda revisa el nodo
    if (n->hasRight()) {
        getLeafs(vector, n->getRight());
    }
    //Si es una hoja lo añade al vector
    if (n->isLeaf()) {
        vector.push_back(n);
    }
}

/**
 * Comprueba si dos árboles son iguales
 * 
 * O(n)
 * 
 * @param other el otro árbol
 * @return si son iguales
 */
template<class K, class V>
bool BinarySearchTree<K, V>::equals(const BinarySearchTree<K, V>& other) const {
    return equals_1(this->p_root, other.p_root);
}

/**
 * Función auxiliar recursiva para comprovar si son iguales
 * 
 * O(n)
 * 
 * @param this_n nodo del propio árbol
 * @param other_n nodo del otro árbol
 * @return si son iguales
 */
template<class K, class V>
bool BinarySearchTree<K, V>::equals_1(BinaryTreeNode<K, V>* this_n, BinaryTreeNode<K, V>* other_n) const {
    if (this_n == nullptr and other_n == nullptr)
        return true;
    if (this_n != nullptr and other_n != nullptr)
        return (*this_n == *other_n && equals_1(this_n->getLeft(), other_n->getLeft()) && equals_1(this_n->getRight(), other_n->getRight()));
    else {
        return false;
    }
}

/**
 * Comprueba si está vacío
 * 
 * O(1)
 * 
 * @return si está vacío
 */
template<class K, class V>
bool BinarySearchTree<K, V>::isEmpty() const {
    return p_root == nullptr;
}

/**
 * Calcular la altura del árbol
 * 
 * O(h) donde h es la altura del árbol
 * 
 * @return altura del árbol
 */
template<class K, class V>
int BinarySearchTree<K, V>::height() const {
    return max_height(p_root);
}

/**
 * Función auxiliar recursivo para calcular la altura máxima del árbol
 * 
 * O(h) donde h es la altura del árbol
 * 
 * @param node nodo recursivo
 * @return altura del árbol
 */
template<class K, class V>
int BinarySearchTree<K, V>::max_height(BinaryTreeNode<K, V>* node) const {
    if (node == nullptr)
        return 0;
    else {
        int left_depth = max_height(node->getLeft());
        int right_depth = max_height(node->getRight());

        if (left_depth < right_depth)
            return right_depth + 1;
        else
            return left_depth + 1;
    }
}

/**
 * Enseña la información del árbol de la forma LVR
 * 
 * O(n)
 * 
 * @param n nodo
 */
template<class K, class V>
void BinarySearchTree<K, V>::showKeysInorder(BinaryTreeNode<K, V>* n) const {
    if (isEmpty())
        cout << "Arbre buit";
    else {
        if (n == nullptr) {
            cout << "|";
            showKeysInorder(p_root);
            cout << endl;
        } else {
            if (n->hasLeft())
                showKeysInorder(n->getLeft());
            cout << " " << n->getKey() << " : [";

            for (int i = 0; i < n->getValues().size(); ++i) {
                std::cout << n->getValues()[i];
                if (i < n->getValues().size() - 1)
                    cout << ",";
            }
            cout << "] |";
            if (n->hasRight())
                showKeysInorder(n->getRight());
        }
    }
}

/**
 * Enseña la información del árbol de la forma LRV
 * 
 * O(n)
 * 
 * @param n nodo
 */
template<class K, class V>
void BinarySearchTree<K, V>::showKeysPostorder(BinaryTreeNode<K, V>* n) const {
    if (isEmpty())
        cout << "Arbre buit";
    else {
        if (n == nullptr) {
            cout << "|";
            showKeysPostorder(p_root);
            cout << endl;
        } else {
            if (n->hasLeft())
                showKeysPostorder(n->getLeft());
            if (n->hasRight())
                showKeysPostorder(n->getRight());

            cout << " " << n->getKey() << " : [";

            for (int i = 0; i < n->getValues().size(); ++i) {
                std::cout << n->getValues()[i];
                if (i < n->getValues().size() - 1)
                    cout << ",";
            }
            cout << "] |";
        }
    }
}

/**
 * Enseña la información del árbol de la forma VLR
 * 
 * O(n)
 * 
 * @param n nodo
 */
template<class K, class V>
void BinarySearchTree<K, V>::showKeysPreorder(BinaryTreeNode<K, V>* n) const {
    if (isEmpty())
        cout << "Arbre buit";
    else {
        if (n == nullptr) {
            cout << "|";
            showKeysPreorder(p_root);
            cout << endl;
        } else {
            cout << " " << n->getKey() << " : [";
            for (int i = 0; i < n->getValues().size(); ++i) {
                std::cout << n->getValues()[i];
                if (i < n->getValues().size() - 1)
                    cout << ",";
            }
            cout << "] |";

            if (n->hasLeft())
                showKeysPreorder(n->getLeft());
            if (n->hasRight())
                showKeysPreorder(n->getRight());
        }
    }
}

/**
 * Tamaño del árbol
 * 
 * O(n)
 * 
 * @return tamaño del árbol
 */
template<class K, class V>
int BinarySearchTree<K, V>::size() const {
    return size_calculator(p_root);
    //return _size;

}

/**
 * Función auxiliar para calcular el tamaño
 * 
 * O(n)
 * 
 * @param node nodo recurso
 * @return tamaño del árbol
 */
template<class K, class V>
int BinarySearchTree<K, V>::size_calculator(BinaryTreeNode<K, V>* node) const {
    if (node == nullptr)
        return 0;
    else
        return (size_calculator(node->getLeft()) + size_calculator(node->getRight()) + 1);
}

/**
 * Devuelve el valor de un nodo con un cierto key
 * 
 * O(h) donde h es la altura del árbol
 * 
 * @param k key
 * @return el vector con todos los valores del key
 */
template<class K, class V>
const vector<V>& BinarySearchTree<K, V>::valuesOf(const K& k) const {
    BinaryTreeNode<K, V>* temp = find(k);
    if (find(k) == nullptr)
        throw invalid_argument("No key found");
    return temp->getValues();
}




#endif /* BINARYSEARCHTREE_H */

