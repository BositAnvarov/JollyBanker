#ifndef BANK_H_
#define BANK_H_

#include <queue>
#include <string>
#include "binary_search_tree.h"
#include "transaction.h"
using namespace std;

class Bank
{
public:
    //constructor - destructor
    Bank();
    Bank (string fileName);
    ~Bank();


    //functions
    void ProcessToBST();
    void PrintDetails();

private:
    BSTree accData_;
    queue<Transaction> list_;
    
};
#endif