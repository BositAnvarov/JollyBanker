#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
using namespace std;

class Transaction
{
	friend ostream& operator<<(ostream& out, const Transaction& rhs);
public:
	// constructors - destructors
	Transaction();
	Transaction(char action, string fName, string lName, int accID);
	Transaction(char action, int accID, int accFundID, int amount);
	Transaction(char action, int accID, int accFundID, int amount, int toAccID, int toFund);
	Transaction(char action, int accID);
	Transaction(char action, int accID, int accFundID);
	Transaction(char action, int accID, int fundID, int amount, int toAccID, int toFund, string fail);
	Transaction(char action, int accID, int fundID, string fail, int amount);
	~Transaction();

	//getters-setters 
	string getFirstName() const;
	string getLastName() const;
	string getFail() const;
	int getAccountID() const;
	int getFundIndex() const;
	int getTransferAcID() const;
	int getTransferFundID() const;
	int getTransactionAmount() const;
	char getActionType() const;

	
	void setTransactionType(char action);
	void setFirstName(string fName);
	void setLastName(string lName);
	void setAccountID(int accID);
	void setAccountFundID(int fundID);
	void setReceivingID(int toAccID);
	void setReceivingFundID(int toFundID);
	void setTransactionAmount(int amount);
	void setFail(string fail);

	// functions
	bool isFailed();

private:
	char actionType_;
	string fName_;
	string lName_;
	string fail_;
	int accID_;
	int fundID_; 
	int toAccID_;
	int toFundID_;
	int amount_;
};
#endif 