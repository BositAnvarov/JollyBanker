#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include <vector>
#include "fund.h"
#include "transaction.h"
using namespace std;

class Account
{
public:
    //constructor-destructor
    Account();
    Account(int accId, string lname, string fname);
    ~Account();

    //getters-setters
    string get_fname() const;
    string get_lname() const;
    int getId() const;

    //functions
    string fund_name(int fundID) const;
    int fund_balance(int fund) const;
    void deposit_fund(int fundID, int amount);
    bool withdraw_funds(int fund, int amount, Transaction& trns);
    void transaction_history(Transaction& tmp, int fundID);
    void withdraw_money(int fundID, int toFundID, int amount);
    void display_account_history();
    void specific_fund_history(int fundID);
    void fail(int amount, string fName, string lName, int fundID);
    
    // overloading operators
    friend ostream& operator<<(ostream& output, const Account& rhs) {
        cout << rhs.get_fname() << " " << rhs.get_lname() << " Account ID: " << rhs.getId() << endl;

        for (int i = 0; i < 8; i++) {
            cout << "  " << rhs.fund_name(i) << ": $" << rhs.fund_balance(i) << "\n";
        }

        return cout;
    }

private:
    string fname_;
    string lname_;
    int accId_;
    Fund fund_[8];
};
#endif 