#include <iostream>
#include "binary_search_tree.h"
using namespace std;

//constructor 
BSTree::BSTree()
{
    root = nullptr;
}


//destructor 
BSTree::~BSTree()
{
    Empty();
}

// add new account to the tree
bool BSTree::Insert(Account* insAcc)
{
    if (root == nullptr)
    {
        root = new Node;
        root->pAcct = insAcc;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }

    else
    {
        Node* tmp = root;
        recursiveInsert(tmp, insAcc);
        return false;
    }
    
}




bool BSTree::Retrieve(const int& accID, Account*& pObj) const
{
    Node* tmp = root;
    while (tmp != nullptr)
    {
        if (tmp->pAcct->getId() == accID)
        {
            pObj = tmp->pAcct;
            return true;
        }

        // left side
        else if (tmp->pAcct->getId() > accID)
        {
            tmp = tmp->left;
        }

        // right side
        else 
        {
            tmp = tmp->right;
        }
    }  
    return false;
}

// check if tree is empty 
bool BSTree::isEmpty() const
{
    return (this->root == nullptr);
}
// clear the tree
void BSTree::Empty()
{
    if (this->root != nullptr)
    {
        recursiveDel(root);
    }
}

// show which accounts in the tree
void BSTree::Display() const
{
    Node* tmp = root;
    if(tmp != nullptr)
    {
        treeDisplay(tmp);
    }
    else 
    {
        cout << "No account exists in the tree!" << endl;
    }
}

bool BSTree::recursiveInsert(Node* tmp, Account* insAcc)
{
    if (insAcc->getId() > tmp->pAcct->getId())
    {
        if (tmp->right == nullptr)
        {
            Node* temp = new Node;
            temp->pAcct = insAcc;
            temp->left = nullptr;
            temp->right = nullptr;
            tmp->right = temp;
            return true;

        }

        else
        {
            recursiveInsert(tmp->right, insAcc);
        }
    }

    else if (insAcc->getId() < tmp->pAcct->getId())
    {
        if (tmp->left == nullptr)
        {
            Node* temp = new Node;
            temp->pAcct = insAcc;
            temp->left = nullptr;
            temp->right = nullptr;
            tmp->left = temp;
            return true;

        }
        else
        {
            recursiveInsert(tmp->left, insAcc);
        }
    }
    else
    {
        return false;
    }
}

void BSTree::treeDisplay(Node* begin) const
{
    if (begin != nullptr)
    {
        treeDisplay(begin->left);

        if (begin == nullptr)
        {
            return;
        }
        else
        {
            cout << *(begin->pAcct) << endl;
        }
        treeDisplay(begin->right);
    }
    
}

// Delete the tree
void BSTree::recursiveDel(Node* delNode)
{
    if (delNode != nullptr)
    {
        recursiveDel(delNode->left);
        recursiveDel(delNode->right);

        //delete from heap to avoid leaks
        delete delNode;
        delNode = nullptr;
    }
    
    
}

