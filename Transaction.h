/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transaction.h
 * Author: li471
 *
 * Created on 21 de abril de 2021, 16:45
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

class Transaction {
public:
    Transaction(string data = "0000-00-00 00:00", int id = 0, float transaccio = 0);
    Transaction(const Transaction& orig);
    virtual ~Transaction();
    
    void print() const;
    string getData() const;
    int getId() const;
    float getQuantitat() const;
    
    void setData(string _data);
    void setId(int _id);
    void setQuantitat(float _quantitat);
      
private:
    string data;
    int id;
    float quantitat;

};

#endif /* TRANSACTION_H */

