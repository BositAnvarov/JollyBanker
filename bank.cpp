#include "bank.h"
#include "account.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>


//constructor
Bank::Bank() 
{
}



//queue to read from file through constructor  
Bank::Bank(string fileName)
{
    ifstream inFile(fileName);

    if (inFile.is_open()) 
    {
        string actionPhrase;
        while (!inFile.eof())
        {

            getline(inFile, actionPhrase);
            if (actionPhrase.empty())
            {
                break;
            }

            char actionType;
            istringstream parse(actionPhrase);
            parse >> actionType;

            // transaction for openning account
            if (actionType == 'O')
            {
                string lname, fname;
                int accID;
                parse >> accID >> lname >> fname;

                Transaction openAcc(actionType, fname, lname, accID);
                list_.push(openAcc);
            }
            
            // D for deposit, W for withdraw
            else if (actionType == 'D' || actionType == 'W')
            {
                int accID, fundID, amount;
                parse >> accID >> fundID >> amount;

                Transaction depositWithdraw(actionType, accID, fundID, amount);
                list_.push(depositWithdraw);
            }

            // assets between funds
            else if (actionType == 'T')
            {
                int accID, fundID, amount, transfAccID, transfFundID;
                parse >> accID >> fundID >> transfAccID >> transfFundID >> amount;
                
                Transaction transfAmount(actionType, accID, fundID, amount, transfAccID, transfFundID);
                list_.push(transfAmount);
            }

            // history of all transactions
            else if (actionType == 'A')
            {
                int accID;
                parse >> accID;

                Transaction trnsHistory(actionType, accID);
                list_.push(trnsHistory);
            }

            // history of given transactions
            else if (actionType == 'F')
            {
                int accID, fundID;
                parse >> accID >> fundID;

                Transaction givenTrnsHistory(actionType, accID, fundID);
                list_.push(givenTrnsHistory);
            }
            else
            {
                cout << "ERROR: The input is INVALID. Transaction CANCELLED" << endl;
            }
        }
    }
}

Bank::~Bank()
{
}




void Bank::ProcessToBST()
{
    
    while (!list_.empty())
    {

        Transaction trns = list_.front(); 
        if (trns.getActionType() == 'O')
        {
            
            Account* newAcc = new Account(trns.getAccountID(), trns.getLastName(), trns.getFirstName());
            accData_.Insert(newAcc);
            
        }

        // to deposit 
        else if (trns.getActionType() == 'D')
        {
            Account* newAcc = nullptr;
            int accID = trns.getAccountID();
            int fundID = trns.getFundIndex();
            int amount = trns.getTransactionAmount();
            
            
            if (accData_.Retrieve(accID, newAcc))
            {
                newAcc->deposit_fund(fundID, amount);
                newAcc->transaction_history(trns, fundID);
            } 
            else 
            {
                cout << "ERROR: No such Account" << endl;
            }
        }

        // to withdraw  
        else if (trns.getActionType() == 'W')
        {
            Account* newAcc = nullptr;
            int accID = trns.getAccountID();
            int fundID = trns.getFundIndex();
            int amount = trns.getTransactionAmount();
            
            //check if account exists 
            if (accData_.Retrieve(accID, newAcc))
            {
                newAcc->withdraw_funds(fundID, amount, trns);
            } 
            else
            {
                cout << "ERROR: Cannot withdraw because the acound does not exist." << endl;
            }
        }

        // to transfer 
        else if (trns.getActionType() == 'T')
        {
            Account* toAcc = nullptr;
            Account* fromAcc = nullptr;

            int fromAccID, fromFundID, amount, toAccID, toFundID;
            fromAccID = trns.getAccountID();
            fromFundID = trns.getFundIndex();
            toAccID = trns.getTransferAcID();
            toFundID = trns.getTransferFundID();
            amount = trns.getTransactionAmount();
            
            // recieving account existance check
            if (accData_.Retrieve(fromAccID, fromAcc) && accData_.Retrieve(toAccID, toAcc))
            {
                if (fromAcc->withdraw_funds(fromFundID, amount, trns))
                {
                    toAcc->deposit_fund(toFundID, amount);
                    toAcc->transaction_history(trns, toFundID);
                }
                else
                {
                    cout << "ERROR: Transfer denied, insufficient fund in account(" <<
                        fromAcc->getId() << ") to transfer to(" << toAcc-> getId() << ") " << endl;


                }
            }
            else 
            {
                cout << "ERROR: Transfer cancelled. No such account" << endl;
            }
        }

        else if (trns.getActionType() == 'A')
        {
            Account* newAcc = nullptr;
            int accID = trns.getAccountID();

            if (accData_.Retrieve(accID, newAcc))
            {
                cout << endl;
                newAcc->display_account_history();
                cout << endl;
            }
        }

        else if (trns.getActionType() == 'F')
        {
            Account* newAcc = nullptr;
            int accID = trns.getAccountID();
            int fundID = trns.getFundIndex();

            if (accData_.Retrieve(accID, newAcc))
            {
                newAcc->specific_fund_history(fundID);
                cout << endl;
            }
        }
        // first action in quee
        list_.pop();
    }
}

// show details
void Bank::PrintDetails()
{
    
    cout << "\nFINAL BALANCES: " << endl;
    accData_.Display();
}