/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManagerAVL.cpp
 * Author: li471
 * 
 * Created on 21 de abril de 2021, 16:57
 */

#include "TransactionManagerAVL.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include<math.h>
using namespace std;

/**
 * Contructor con parámetros  1
 * 
 * @param buyingFee tasas de compra
 * @param sellingFee tasas de venta
 */
TransactionManagerAVL::TransactionManagerAVL(float buyingFee, float sellingFee) : AVLTree<string, Transaction>() {
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

/**
 * Constructor con parámetros 2
 * @param file_path ruta fichero
 * @param buyingFee tasas de compra
 * @param sellingFee tasas de venta
 */
TransactionManagerAVL::TransactionManagerAVL(string file_path, float buyingFee, float sellingFee) : AVLTree<string, Transaction>() {
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
    loadFromFile(file_path);
}

/**
 * Destructor
 */
TransactionManagerAVL::~TransactionManagerAVL() {
}

/**
 * Va mostrando todos los elementos del árbol cronológicamente de lo mas viejo a lo mas nuevo según la petición del usuario
 * 
 * Coste O(n) donde n en el peor de los casos es el tamaño del árbol.
 */
void TransactionManagerAVL::showAll() const {
    if (isEmpty()) {
        cout << "Encara no hi ha transaccions" << endl;
    } else {
        stack<BinaryTreeNode<string, Transaction>*> temp;
        BinaryTreeNode<string, Transaction>* temp_node = p_root;
        int comptador = 0, fi = number_asker();
        while ((!temp.empty() || temp_node != nullptr) && comptador < fi) {
            if (temp_node != nullptr) {
                temp.push(temp_node);
                temp_node = temp_node->getLeft();
            } else {
                temp_node = temp.top();
                temp.pop();
                vector<Transaction> vect = temp_node->getValues();
                for (int i = 0; i < vect.size(); i++) {
                    vect[i].print();
                    cout << endl;
                }
                temp_node = temp_node->getRight();
                comptador++;
                if (comptador == fi) {
                    int temp = number_asker();
                    if (temp > 0)
                        fi += temp;
                }
            }
        }
    }
}

/*
void TransactionManagerAVL::showAll_recursive() const {
    int comptador = 0, fi = 10000000;
    showAll_recursive(comptador, fi, p_root);
}

void TransactionManagerAVL::showAll_recursive(int& comptador, int& fi, BinaryTreeNode<string, Transaction>* n) const {
    if (comptador < fi) {
        if (n->hasLeft())
            showAll_recursive(comptador, fi, n->getLeft());
        vector<Transaction> vect = n->getValues();
        for (int i = 0; i < vect.size(); i++) {
            //vect[i].print();
            //cout << endl;
        }
        comptador++;
        if (comptador == fi) {
            int temp = number_asker();
            if (temp > 0)
                fi += temp;
        }
        if (n->hasRight())
            showAll_recursive(comptador, fi, n->getRight());
    }
}*/


int TransactionManagerAVL::fileExists(string const& name) {
    ifstream f(name.c_str());
    if (!f.good())
        throw invalid_argument("Fitxer no trobat");
    return 0;
}

void TransactionManagerAVL::splitter(string const & _string, const char delimiter, vector<string> &output) {
    stringstream string_s(_string);
    string save;
    while (getline(string_s, save, delimiter)) {
        output.push_back(save);
    }
}

/**
 * Carga la información de un fichero en el árbol
 * 
 * Coste O(nh) donde n es el número de elementos a leer y h es la altura del árbol.
 * 
 * @param file_path fichero de donde se quiere cargar la información
 */
void TransactionManagerAVL::loadFromFile(string file_path) {
    fstream fichero;
    string frase;
    //Programa principal
    fileExists(file_path);
    fichero.open(file_path);
    cout << "Reading file " << file_path << "...\n";
    while (!fichero.eof()) {
        vector<string> informacio;
        //Llegida de la linea
        getline(fichero, frase);
        //Es fa split de l'input
        if (frase != "") {
            splitter(frase, ',', informacio);
            try {
                Transaction newTransaction(informacio[0], stoi(informacio[1]), stof(informacio[2]));
                AVLTree<string, Transaction>::add(informacio[0], newTransaction);
            } catch (exception const& e) {
                cout << "Error al afegir una transacció.\n";
            }
        }
    }
    cout << endl << endl;
    fichero.close();
}

/**
 * Muestr apor pantalla la transacción más vieja.
 * 
 * Coste O(h) donde h es la altura del árbol
 */
void TransactionManagerAVL::showOldest() const {
    BinaryTreeNode<string, Transaction> *temp = this->p_root;
    while (temp->hasLeft())
        temp = temp->getLeft();
    vector<Transaction> vect = temp->getValues();
    for (int i = 0; i < vect.size(); i++) {
        vect[i].print();
        cout << endl;
    }
}

/**
 * Muestra por pantalla la transacción más nueva.
 * 
 * Coste O(h) donde h es la altura del árbol
 */
void TransactionManagerAVL::showNewest() const {
    BinaryTreeNode<string, Transaction> *temp = this->p_root;
    while (temp->hasRight())
        temp = temp->getRight();
    vector<Transaction> vect = temp->getValues();
    for (int i = 0; i < vect.size(); i++) {
        vect[i].print();
        cout << endl;
    }
}

/**
 * Pregunta un número al usuario
 * 
 * @return número que ha introducido el usuario
 */
int TransactionManagerAVL::number_asker() const {
    cout << "Quants transaccions vol imprimir?" << endl;
    int temp;
    cin >> temp;
    return temp;
}

/**
 * Va mostrando todos los elementos del árbol cronológicamente de lo mas nuevo a lo mas viejo según la petición del usuario
 * 
 * Coste O(n) donde n en el peor de los casos es el tamaño del árbol
 */
void TransactionManagerAVL::showAllReverse() const {
    if (isEmpty()) {
        cout << "Encara no hi ha transaccions" << endl;
    } else {
        stack<BinaryTreeNode<string, Transaction>*> temp;
        BinaryTreeNode<string, Transaction>* temp_node = p_root;
        int comptador = 0, fi = number_asker();
        while ((!temp.empty() || temp_node != nullptr) && comptador < fi) {
            if (temp_node != nullptr) {
                temp.push(temp_node);
                temp_node = temp_node->getRight();
            } else {
                temp_node = temp.top();
                temp.pop();
                vector<Transaction> vect = temp_node->getValues();
                for (int i = 0; i < vect.size(); i++) {
                    vect[i].print();
                    cout << endl;
                }
                temp_node = temp_node->getLeft();
                comptador++;
                if (comptador == fi) {
                    int temp = number_asker();
                    if (temp > 0)
                        fi += temp;
                }
            }
        }
    }
}

/**
 * Devuelve las tasas totales de todas las trasacciones
 * 
 * Coste O(n) donde n es el tamaño del árbol
 * 
 * @return la suma de todas las tasas de las transacciones
 */
float TransactionManagerAVL::feesInTotal() const {
    if (isEmpty())
        return 0;
    else {
        stack<BinaryTreeNode<string, Transaction>*> temp;
        BinaryTreeNode<string, Transaction>* temp_node = p_root;
        float tases;
        while ((!temp.empty() || temp_node != nullptr)) {
            if (temp_node != nullptr) {
                temp.push(temp_node);
                temp_node = temp_node->getLeft();
            } else {
                temp_node = temp.top();
                temp.pop();
                vector<Transaction> vect = temp_node->getValues();
                for (int i = 0; i < vect.size(); i++) {
                    if (vect[i].getQuantitat() < 0)
                        tases += buyingFee * vect[i].getQuantitat()*-1;
                    else
                        tases += sellingFee * vect[i].getQuantitat();
                }
                temp_node = temp_node->getRight();
            }
        }
        return tases;
    }
}

/*
 * LEER INTERVALO FORMA ITERATIVA POCO EFICIENTE
 * 
 * float TransactionManagerAVL::feesInTimeInterval(pair<string, string> interval) const {
    if (isEmpty())
        return 0;
    else {
        string p_1, p_2;
        if (interval.first > interval.second) {
            p_1 = interval.first;
            p_2 = interval.second;
        } else {
            p_1 = interval.second;
            p_2 = interval.first;
        }
        stack<BinaryTreeNode<string, Transaction>*> temp;
        BinaryTreeNode<string, Transaction>* temp_node = p_root;
        float tases = 0;
        bool fi = false;
        while ((!temp.empty() || temp_node != nullptr) && !fi) {
            if (temp_node != nullptr) {
                temp.push(temp_node);
                temp_node = temp_node->getLeft();
            } else {
                temp_node = temp.top();
                temp.pop();
                if (temp_node->getKey() >= p_2 and temp_node->getKey() <= p_1) {
                    vector<Transaction> vect = temp_node->getValues();
                    for (int i = 0; i < vect.size(); i++) {
                        if (vect[i].getQuantitat() < 0)
                            tases += buyingFee * vect[i].getQuantitat()*-1;
                        else
                            tases += sellingFee * vect[i].getQuantitat();
                    }
                } else if (temp_node->getKey() > p_1) {
                    fi = true;
                }
                temp_node = temp_node->getRight();
            }
        }
        return tases;
    }
}*/

/**
 * Devuelve las tasas en un intervalo de tiempo
 * 
 * Coste O(h+n) donde n es el número de transacciones dentro del intervalo y h la altura del árbol
 * 
 * @param interval el intervalo de tiempo donde se quiere calcular las tasas
 * @return las tasas en ese determinado intervalo
 */
float TransactionManagerAVL::feesInTimeInterval(pair<string, string> interval) const {
    float fee = 0;
    string p_1;
    if (interval.first < interval.second) {
        p_1 = interval.first;
        interval.first = interval.second;
        interval.second = p_1;
    }
    fee_calculator(interval, p_root, fee);
    return fee;
}

/**
 * Función auxiliar recursiva para calcular las tasas en un intervalo
 * 
 * Coste O(h+n) donde n es el número de transacciones dentro del intervalo y h la altura del árbol
 * 
 * @param interval intervalo en el que se quiere calcular las tasas 
 * @param n parámetro recursivo
 * @param fee tasas totales en ese intervalo
 */
void TransactionManagerAVL::fee_calculator(pair<string, string> interval, BinaryTreeNode<string, Transaction>* n, float& fee) const {
    if (n != nullptr) {
        if (interval.second < n->getKey())
            fee_calculator(interval, n->getLeft(), fee);
        if (n->getKey() >= interval.second and n->getKey() <= interval.first) {
            vector<Transaction> vect = n->getValues();
            for (int i = 0; i < vect.size(); i++) {
                if (vect[i].getQuantitat() < 0)
                    fee += buyingFee * vect[i].getQuantitat()*-1;
                else
                    fee += sellingFee * vect[i].getQuantitat();
            }
        }
        if (interval.first > n->getKey())
            fee_calculator(interval, n->getRight(), fee);
    }
}

float TransactionManagerAVL::feesSinceTime(string date) const {
    if (isEmpty())
        return 0;
    else {
        stack<BinaryTreeNode<string, Transaction>*> temp;
        BinaryTreeNode<string, Transaction>* temp_node = p_root;
        float tases;
        bool fi = false;
        while ((!temp.empty() || temp_node != nullptr) && !fi) {
            if (temp_node != nullptr) {
                temp.push(temp_node);
                temp_node = temp_node->getRight();
            } else {
                temp_node = temp.top();
                temp.pop();
                if (temp_node->getKey() >= date) {
                    vector<Transaction> vect = temp_node->getValues();
                    for (int i = 0; i < vect.size(); i++) {
                        if (vect[i].getQuantitat() < 0)
                            tases += buyingFee * vect[i].getQuantitat()*-1;
                        else
                            tases += sellingFee * vect[i].getQuantitat();
                    }
                } else {
                    fi = true;
                }
                temp_node = temp_node->getLeft();
            }
        }
        return tases;
    }
}
/*
float TransactionManagerAVL::feesSinceTime(string date) const {
    return feesSinceTime("0");
}*/














