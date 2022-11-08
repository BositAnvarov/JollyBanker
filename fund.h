#ifndef FUND_H_
#define FUND_H_
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "transaction.h"

using namespace std;

class Fund
{
public:
    //constructor
    Fund();
    ~Fund();

    //getters-setters
    string getName() const;
    int getBalance() const;
    void set_name(string fundName);
    void setBalance(int totalBalance);
    

    // Functions
    bool AddFunds(int add);
    bool SubtractFunds(int sub);
    bool trnsHistory(Transaction& );
    void spTrnsHistory();
    void allTrnsHistory();

private:
    int totalBalance_;
    string fundName_;
    vector<Transaction> trnsHistory_;
};
#endif