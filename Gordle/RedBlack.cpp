#include "RedBlack.h"
#include <iostream>

//-------------------------------------------Helper Functions---------------------------------------------//

//----------------Rotation Functions-------------//
//---------Left Rotation----------// O(1)
RedBlack::TreeNode* RedBlack::rotateLeft(TreeNode* node)
{
    //Gets right node
    TreeNode* newNode = node->right;
    node->right = newNode->left;
    if (newNode->left) {
        newNode->left->parent = node;
    }
    //Switches parents
    newNode->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = newNode;
    }
    else if (node == node->parent->left) {
        node->parent->left = newNode;
    }
    else {
        node->parent->right = newNode;
    }
    //Does final switch for the rotation
    newNode->left = node;
    node->parent = newNode;
    return newNode;
}

//---------Right Rotation----------// O(1)
RedBlack::TreeNode* RedBlack::rotateRight(TreeNode* node)
{
    //Gets left node
    TreeNode* newNode = node->left;
    node->left = newNode->right;
    if (newNode->right)
        newNode->right->parent = node;
    //Switches parents
    newNode->parent = node->parent;
    if (!node->parent)
        this->root = newNode;
    
    else if (node == node->parent->right)
        node->parent->right = newNode;
    else
        node->parent->left = newNode;
    //Does final switch for the rotation
    newNode->right = node;
    node->parent = newNode;
    return newNode;
}

//-------------Balances tree recursively and re-balances if needed------------// 
RedBlack::TreeNode* RedBlack::balanceTree(TreeNode* kid)
{
    TreeNode* uncle;
    TreeNode* grand;
    if (kid->parent != nullptr) {
        //Using while loop due to odd stack overflow behavior
        while (kid->parent->color == RED) {
            grand = kid->parent->parent;
            //If uncle is the left sibling
            if (kid->parent == grand->right) {
                uncle = grand->left;
                //If Uncle is valid and red
                if (uncle && uncle->color == RED) { 
                    uncle->flip();
                    kid->parent->flip();
                    grand->flip();
                    kid = grand;
                }
                //If Uncle is either invalid or black
                else {
                    //Does aditional step if kid is left sibling
                    if (kid == kid->parent->left) { 
                        kid = kid->parent;
                        rotateRight(kid);
                    }
                    //Flips colors of parent and grandparent
                    kid->parent->flip();
                    grand->flip();
                    rotateLeft(grand);
                }
                
            }
            //If uncle is the right sibling
            else {
                uncle = grand->right; 
                //If Uncle is valid and red
                if (uncle && uncle->color == RED) { 
                    uncle->flip();
                    kid->parent->flip();
                    grand->flip();
                    kid = grand;
                }
                //If Uncle is either invalid or black
                else {
                    //Does aditional step if kid is left sibling
                    if (kid == kid->parent->right) {
                        kid = kid->parent;
                        rotateLeft(kid);
                    }
                    //Flips colors of parent and grandparent
                    kid->parent->flip();
                    grand->flip();
                    rotateRight(grand);
                }
            }
            //Stops while loop if the new kid is the root
            if (kid == this->root)
                break;
        }
    }


    root->color = BLACK;
    return root;
}

//------------------------------------------Constructors/Destructor----------------------------------------//

//--------Construtor---------//
RedBlack::RedBlack()
{
    root = nullptr;
    numItems = 0;
}

//----------Destructor---------//
RedBlack::~RedBlack()
{
    //Collects and delete all nodes inside tree
    for (auto i : allNodes) {
        delete i;
    }
    this->root = nullptr;
}

//---------------------------------------------------Public Functions-------------------------------------------//
//--------Main Insert Command---------//
void RedBlack::insert(std::string name)
{
    TreeNode* root = this->root;
    TreeNode* parent;
    bool isHere = false;

    TreeNode* temp = new TreeNode(name);
    //Sets temp as root if only node
    if (numItems == 0) {
        this->root = temp;
    }
    else {
        //Implemented in while loop to fix stack overflow errors
        while (root) {
            //If name already exists, then don't add root
            if (name == root->name) {
                delete temp;
                return;
            }
            //Does usual binary search, adds temp to proper area
            if (name < root->name) {
                if (!root->left) {
                    root->left = temp;
                    temp->parent = root;
                    break;
                }
                root = root->left;
            }
            else {
                if (!root->right) {
                    root->right = temp;
                    temp->parent = root;
                    break;
                }
                root = root->right;
            }
        }
    }
    numItems++;
    
    //Push node into list for delete and random word play
    allNodes.push_back(temp);
    
    //If it is the root
    if (!temp->parent) {
        temp->color = BLACK;
    //If the grandparent is a valid tree
    } else if (temp->parent->parent) {
        balanceTree(temp);
    }


    //std::cout << "successful" << std::endl;
}

//----------Searches entire tree name---------//
bool RedBlack::find(std::string name)
{
    TreeNode* root = this->root;
    //Searches using while loop to fix stack overflow
    while (root) {
        if (name == root->name) {
            return true;
        }
        if (name < root->name) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return false;
}

//Gets random word from node list
std::string RedBlack::randomWord(int goTo)
{
    int count = 0;
    for (auto i : allNodes) {
        if (count >= goTo)
            return i->name;
        count++;
    }

   return "among";
}
