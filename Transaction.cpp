/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transaction.cpp
 * Author: li471
 * 
 * Created on 21 de abril de 2021, 16:45
 */

#include "Transaction.h"
#include <iostream>
#include<iomanip>
using namespace std;

Transaction::Transaction(string data, int id, float transaccio) {
    this->data = data;
    this->id = id;
    this->quantitat = transaccio;
}


Transaction::Transaction(const Transaction& orig) {
    data = orig.data;
    id = orig.id;
    quantitat = orig.quantitat;
}

Transaction::~Transaction() {
}

string Transaction::getData() const {
    return data;
}

int Transaction::getId() const {
    return id;
}

float Transaction::getQuantitat() const {
    return quantitat;
}

void Transaction::print() const {
    string datos = data +","+to_string(id) +","+to_string(quantitat);
    int len = datos.length();
    if(len < 35){
        for(int i = len ; i<35;i++)
            datos += " ";
    }
    cout <<datos;
}

void Transaction::setData(string _data) {
    data = _data;
}

void Transaction::setId(int _id) {
    id = _id;
}

void Transaction::setQuantitat(float _quantitat) {
    quantitat = _quantitat;
}











