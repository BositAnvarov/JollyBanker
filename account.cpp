#include <iostream>
#include "account.h"

using namespace std;

// default constructor
Account::Account()
{
	accId_ = -1;
	fname_ = "Nameless";
	lname_ = "Account";
	fund_[0].set_name("Money Market");
	fund_[1].set_name("Prime Money Market");
	fund_[2].set_name("Long-Term Bond");
	fund_[3].set_name("Short-Term Bond");
	fund_[4].set_name("500 Index Fund");
	fund_[5].set_name("Capital Value Fund");
	fund_[6].set_name("Growth Equity Fund");
	fund_[7].set_name("Growth Index Fund");
	
}

Account::Account(int id, string lname, string fname)
{
	accId_ = id;
	lname_ = lname;
	fname_ = fname;
	fund_[0].set_name("Money Market");
	fund_[1].set_name("Prime Money Market");
	fund_[2].set_name("Long-Term Bond");
	fund_[3].set_name("Short-Term Bond");
	fund_[4].set_name("500 Index Fund");
	fund_[5].set_name("Capital Value Fund");
	fund_[6].set_name("Growth Equity Fund");
	fund_[7].set_name("Growth Index Fund");



}

Account::~Account()
{

}

int Account::getId() const
{
	return accId_;
}

string Account::get_fname() const
{
	return fname_;
}

string Account::get_lname() const
{
	return lname_;
}

string Account::fund_name(int fundID) const
{
	return fund_[fundID].getName();
}

int Account::fund_balance(int fundID) const
{
	return fund_[fundID].getBalance();
}


void Account::deposit_fund(int fundID, int amount)
{
	fund_[fundID].AddFunds(amount);
}


bool Account::withdraw_funds(int fundID, int amount, Transaction& tmp)
{
	if (amount < 0)
	{
		cout << "ERROR: Withdrawl from " << fname_ << " " << lname_ << "'s " << fund_[fundID].getName() << " must be positive. $" << amount << " not withdrawn." << endl;
		tmp.setFail("Withdraw");
		fund_[fundID].trnsHistory(tmp);
		return false;
	}
	if (fund_[fundID].getBalance() >= amount)
	{
		fund_[fundID].SubtractFunds(amount);
		fund_[fundID].trnsHistory(tmp);
		return true;
	}
	else if (fundID <= 1 && fund_[0].getBalance() + fund_[1].getBalance() >= amount)
	{
		if (fundID == 0)
		{
			withdraw_money(0, 1, amount);
			return true;
		}
		else if (fundID == 1)
		{
			withdraw_money(1, 0, amount);
			return true;
		}

	}
	else if (fundID <= 3 && fund_[2].getBalance() + fund_[3].getBalance() >= amount)
	{
		if (fundID == 2)
		{
			withdraw_money(2, 3, amount);
			return true;
		}
		else if (fundID == 3)
		{
			withdraw_money(3, 2, amount);
			return true;
		}
	}
	else 
	{
		cout << "ERROR: Not enough funds to withdraw $" << amount << " from " << fname_ << " " << lname_ << " " << fund_[fundID].getName() << "." << endl;
		tmp.setFail("Withdraw");
		fund_[fundID].trnsHistory(tmp);
		return false;
	}
	return false;
}

// transaction history 
void Account::transaction_history(Transaction& tmp, int fundID)
{
	fund_[fundID].trnsHistory(tmp);
}

// withdraw money 
void Account::withdraw_money(int fundID, int toFundID, int amount)
{
	if (((fund_[fundID].getBalance() + fund_[toFundID].getBalance()) <= amount))
	{
		int totBalance = fund_[fundID].getBalance();
		if (totBalance > amount)
		{
			fund_[fundID].SubtractFunds(totBalance);
			Transaction subtract('W', getId(), fundID, totBalance);
			fund_[fundID].trnsHistory(subtract);
			amount -= totBalance;
		}

		if (fund_[toFundID].getBalance() < amount)
		{
			fail(amount, fname_, lname_, fundID);
		}
		else
		{
			fund_[toFundID].SubtractFunds(amount);
			Transaction subtract('W', getId(), toFundID, amount);
			fund_[toFundID].trnsHistory(subtract);
		}
		
	}
	else
	{
		// first subtraction
		int totBalance = fund_[fundID].getBalance();
		fund_[fundID].SubtractFunds(totBalance);
		Transaction subtract('W', getId(), fundID, totBalance);
		fund_[fundID].trnsHistory(subtract);
		amount -= totBalance;

		//second subtraction
		fund_[toFundID].SubtractFunds(amount);
		Transaction sub_sec('W', getId(), toFundID, amount);
		fund_[toFundID].trnsHistory(sub_sec);
	}
}

// display account history
void Account::display_account_history()
{
	cout << "Transaction History for " << fname_ << " " << lname_ << " " << "by Fund." << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << fund_[i].getName() << ": $" << fund_[i].getBalance() << endl;
		fund_[i].spTrnsHistory();
		
	}
}

//show specific fund history 
void Account::specific_fund_history(int fundID)
{
	cout << "Transaction History for " << fname_ << " " << lname_ << " " << fund_name(fundID) << ": $" << fund_balance(fundID) << endl;
	fund_[fundID].spTrnsHistory();
}

// handle fails
void Account::fail(int amount, string fName, string lName, int fundID)
{
	cout << "ERROR: Not enough funds to withdraw " << amount << " from " << fname_ << " " << lname_<< " " << fund_name(fundID) << endl;

	Transaction fail('W', getId(), fundID, "Failed", amount);
	fund_[fundID].trnsHistory(fail);
}
