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

template<class K, class V>
BinarySearchTree<K, V>::BinarySearchTree() {
    p_root = nullptr;
    _size = 0;

}

template<class K, class V>
BinarySearchTree<K, V>::BinarySearchTree(const BinarySearchTree<K, V>& orig) {
    p_root = new BinaryTreeNode<V, K>(*orig.p_root);
    _size = orig._size;
}

template<class K, class V>
BinarySearchTree<K, V>::~BinarySearchTree() {
    cout << "Destruint l'arbre" << endl;
    delete p_root;
    cout << "..." << endl << "Arbre binari destruit" << endl << endl;
}

template<class K, class V>
BinaryTreeNode<K, V>* BinarySearchTree<K, V>::add(const K& k, const V& value) {
    BinaryTreeNode<K, V> *newNode = new BinaryTreeNode<K, V>(k);
    newNode->addValue(value);
    if (p_root == nullptr)
        p_root = newNode;
    else {
        BinaryTreeNode<K, V>* temp = leave_finder(k, p_root);
        if (temp == nullptr) {
            delete newNode;
            throw invalid_argument("Key exists");
        } else if (temp->getKey() > k) {
            temp->setLeft(newNode);
        } else {
            temp->setRight(newNode);
        }
        newNode->setPare(temp);
    }
    _size++;
}

template<class K, class V>
bool BinarySearchTree<K, V>::has(const K& k) const {
    if (leave_finder(k) == nullptr)
        return true;
    else
        return false;
}

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

template<class K, class V>
BinaryTreeNode<K, V>* BinarySearchTree<K, V>::find(const K& k) const {
    BinaryTreeNode<K, V> *temp = p_root;
    while (temp != nullptr and temp->getKey() != k) {
        if (temp->getKey() > k) {
            temp = temp ->getLeft();
        } else {
            temp = temp ->getRight();
        }
    }
    return temp;
}

template<class K, class V>
vector<BinaryTreeNode<K, V>*> BinarySearchTree<K, V>::getLeafs() {
    vector<BinaryTreeNode<K, V>*> vector;
    getLeafs(vector, p_root);
    return vector;
}

template<class K, class V>
void BinarySearchTree<K, V>::getLeafs(vector<BinaryTreeNode<K, V>*>& vector, BinaryTreeNode<K, V>* n) const {
    if (n->hasLeft()) {
        getLeafs(vector, n->getLeft());
    }
    if (n->hasRight()) {
        getLeafs(vector, n->getRight());
    }
    if (n->isLeaf()) {
        vector.push_back(n);
    }
}

template<class K, class V>
bool BinarySearchTree<K, V>::equals(const BinarySearchTree<K, V>& other) const {
    return equals_1(this->p_root, other.p_root);
}

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

template<class K, class V>
bool BinarySearchTree<K, V>::isEmpty() const {
    return p_root == nullptr;
}

template<class K, class V>
int BinarySearchTree<K, V>::height() const {
    return max_height(p_root);
}

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


template<class K, class V>
int BinarySearchTree<K, V>::size() const {
    //return size_calculator(p_root);
    return _size;

}


template<class K, class V>
int BinarySearchTree<K, V>::size_calculator(BinaryTreeNode<K, V>* node) const {
    if (node == nullptr)
        return 0;
    else
        return (size_calculator(node->getLeft()) + size_calculator(node->getRight()) + 1);
}


template<class K, class V>
const vector<V>& BinarySearchTree<K, V>::valuesOf(const K& k) const {
    BinaryTreeNode<K, V>* temp = find(k);
    if (find(k) == nullptr)
        throw invalid_argument("No key found");
    return find(k)->getValues();
}




#endif /* BINARYSEARCHTREE_H */

