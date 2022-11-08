#include "fund.h"

// default constructor 
Fund::Fund()
{
    fundName_ = "Unnamed Fund";
    totalBalance_ = 0;
    
}
// destructor
Fund::~Fund()
{
}


void Fund::set_name(string name)
{

    fundName_ = name;

}

void Fund::setBalance(int balance)
{
    // control negatives
    if (balance < 0)
    {
        cout << "Balance can not be negative" << endl;
        totalBalance_ = 0;
    }

    totalBalance_ = balance;
    
}

string Fund::getName() const
{
    return fundName_;
}

int Fund::getBalance() const
{
    return totalBalance_;
}

// add funds to the total balance
bool Fund::AddFunds(int amount)
{
    totalBalance_ += amount;
    return true;
}

// subtract money from the total balance 
bool Fund::SubtractFunds(int amount)
{
    totalBalance_ -= amount;
    return true;
}

// record transaction history
bool Fund::trnsHistory(Transaction& trans)
{
    trnsHistory_.push_back(trans);
    return true;
}


// specific fund history 
void Fund::spTrnsHistory()
{
    for (int i = 0; i < trnsHistory_.size(); i++)
    {
        cout << " " << trnsHistory_[i];
    }
}

// print all transaction history 
void Fund::allTrnsHistory()
{
    cout << fundName_ << ": $" << totalBalance_ << endl;

    if (trnsHistory_.size() != 0) {
        for (int i = 0; i < trnsHistory_.size(); i++)
        {
            cout << " " << trnsHistory_[i];
        }
    }
}