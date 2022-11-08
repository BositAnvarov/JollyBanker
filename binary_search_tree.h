#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <iostream>
#include "account.h"
using namespace std;

class BSTree
{
public:
    // constructor-destructor
    BSTree();
    ~BSTree();

    // functions
    bool Insert(Account* ); 
    bool Retrieve(const int& , Account*& ) const;
    void Display() const;
    void Empty();
    bool isEmpty() const;
    
private:
    struct Node
    {
        Account* pAcct;
        Node* right;
        Node* left;
    };
    Node* root;

    bool recursiveInsert(Node* tmpNode, Account* insAcc);
    void treeDisplay(Node* begin) const;
    void recursiveDel(Node* deleteNode);
};
#endif 