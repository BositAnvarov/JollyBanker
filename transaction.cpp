#include "transaction.h"
#include <string>
#include <iostream>
using namespace std;

//default constructors 
Transaction::Transaction()
{
    actionType_ = ' ';
    fName_ = "";
    lName_ = "";
    accID_ = 0;
    fundID_ = 0;
    toAccID_ = 0;
    toFundID_ = 0;
    amount_ = 0;
}

// oppening account constructor 
Transaction::Transaction(char action, string fName, string lName, int accID)
{
    actionType_ = action;
    fName_ = fName;
    lName_ = lName;
    accID_ = accID;
}

// depository constructor
Transaction::Transaction(char action, int accID, int fundID, int amount)
{
    actionType_ = action;
    accID_ = accID;
    fundID_ = fundID;
    amount_ = amount;
}

//transferring constructor
Transaction::Transaction(char action, int accID, int fundID, int amount, int toAccID, int toFundID)
{
    actionType_ = action;
    accID_ = accID;
    fundID_ = fundID;
    amount_ = amount;
    toAccID_ = toAccID;
    toFundID_ = toFundID;
}

//account history constructor 
Transaction::Transaction(char action, int accID)
{
    actionType_ = action;
    accID_ = accID;
}

// specific fund constructor
Transaction::Transaction(char action, int accID, int fundID)
{
    actionType_ = action;
    accID_ = accID;
    fundID_ = fundID;
}

//failed transfer constructor 
Transaction::Transaction(char action, int accID, int fundID, int amount, int toAccID, int toFundID, string fail)
{
    actionType_ = action;
    accID_ = accID;
    fundID_ = fundID;
    amount_ = amount;
    toAccID_ = toAccID;
    toFundID_ = toFundID;
    fail_ = fail;
}

Transaction::Transaction(char action, int accID, int fundID, string fail, int amount)
{
    actionType_ = action;
    accID_ = accID;
    fundID_ = fundID;
    fail_ = fail;
    amount_ = amount;
}

// destructor 
Transaction::~Transaction()
{
}

 
string Transaction::getFirstName() const
{
    return fName_;
}

string Transaction::getLastName() const
{
    return lName_;
}

char Transaction::getActionType() const
{
    return actionType_;
}

int Transaction::getAccountID() const
{
    return accID_;
}

int Transaction::getFundIndex() const
{
    return fundID_;
}

int Transaction::getTransferAcID() const
{
    return toAccID_;
}

int Transaction::getTransferFundID() const
{
    return toFundID_;
}

int Transaction::getTransactionAmount() const
{
    return amount_;
}

string Transaction::getFail() const
{
    return fail_;
}

//setters 
void Transaction::setTransactionType(char action)
{
    actionType_ = action;
}

void Transaction::setFirstName(string name)
{
    fName_ = name;
}

void Transaction::setLastName(string name)
{
    lName_ = name;
}

void Transaction::setAccountID(int accID)
{
    accID_ = accID;
}

void Transaction::setAccountFundID(int accFundID)
{
    fundID_ = accFundID;
}

void Transaction::setReceivingID(int toAccID)
{
    toAccID_ = toAccID;
}

void Transaction::setReceivingFundID(int toFundID)
{
    toFundID_ = toFundID;
}

void Transaction::setTransactionAmount(int amount)
{
    amount_ = amount;
}

void Transaction::setFail(string fail)
{
    fail_ = fail;
}

// check for failure
bool Transaction::isFailed()
{
    if (!fail_.empty()) 
    {
        return false;
    }
    return true;
}

// output overload
ostream& operator<<(ostream& cout, const Transaction& rhs)
{
    if (rhs.fail_.empty()) 
    {

        if (rhs.actionType_ == 'W' || rhs.actionType_ == 'D')
        {
            cout << " " << rhs.actionType_ << " " << rhs.accID_ << " " << rhs.fundID_ << " " << rhs.amount_ << endl;
        
        }
        else if (rhs.actionType_ == 'T')
        {
            cout << " " << rhs.actionType_ << " " << rhs.accID_ << " " << rhs.fundID_ << " " << rhs.toAccID_ << " " << rhs.toFundID_ << " " << rhs.amount_ << endl;
        }
    }
    else if (!rhs.fail_.empty()) 
    {
        if (rhs.actionType_ == 'W')
        {
            cout << " " << rhs.actionType_ << " " << rhs.accID_ << " " << rhs.fundID_ << " " << rhs.amount_ << " FAILED" << endl;
        }
        else if (rhs.actionType_ == 'T')
        {
            cout << " " << rhs.actionType_ << " " << rhs.accID_ << " " << rhs.fundID_ << " " << rhs.toAccID_ << " " << rhs.toFundID_ << " " << rhs.amount_ << " FAILED " << endl;
        }
    }
    return cout;
 }