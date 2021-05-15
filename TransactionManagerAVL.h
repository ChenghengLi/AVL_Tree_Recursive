/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManagerAVL.h
 * Author: li471
 *
 * Created on 21 de abril de 2021, 16:57
 */

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "AVLTree.h"
#include "Transaction.h"
#include <string>

class TransactionManagerAVL : protected AVLTree<string, Transaction> {
public:
    TransactionManagerAVL(float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManagerAVL(string file_path, float buyingFee = 0.02, float sellingFee = 0.03);
    virtual ~TransactionManagerAVL();

    void loadFromFile(string file_path);
    void showAll() const;
    void showAllReverse() const;
    //void showAll_recursive() const;
    void showOldest() const;
    void showNewest() const;

    float feesInTotal() const;
    float feesSinceTime(string date) const;
    float feesInTimeInterval(pair<string, string> interval) const;
    float queries_calculator(string file_path);
private:
    float sellingFee;
    float buyingFee;
    int fileExists(string const& name);
    void splitter(string const & _string, const char delimiter, vector<string> &output);
    int number_asker() const;
    //void showAll_recursive(int& comptador, int& fi, BinaryTreeNode<string, Transaction>* n) const;
    void fee_calculator(pair<string, string> interval, BinaryTreeNode<string, Transaction>* n, float& fee) const;

};

#endif /* TRANSACTIONMANAGER_H */

