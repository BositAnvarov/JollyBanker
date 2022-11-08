#include <iostream>
#include <string>
#include "bank.h"
using namespace std;

int main(int argc, char* argv[])
{
    // get .txt file from command line
    if (argc == 2)
    {
        string filename = argv[1];
        Bank jollyBank(filename);
        jollyBank.ProcessToBST();
        jollyBank.PrintDetails(); 
    } 
    else
    {
        cout << "Input a filename in the arguement ('filename.txt')" << endl;
        return -1;
    }
    

    /*
        Bank jollyBank2("bank_trans_in.txt");
        jollyBank2.ProcessToBST();
        jollyBank2.PrintDetails(); 
    */
}

