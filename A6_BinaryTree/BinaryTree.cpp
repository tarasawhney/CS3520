#include "BinaryTree.hpp"

// C++ Standard Library files
#include <iostream>
#include <algorithm>

// Constructor implementation
BinaryTree::BinaryTree(){
    m_root = nullptr;
}

//creating a destroy_tree function 
void BinaryTree::destroy_tree(BinaryNode* node){

    if (node != nullptr) {
        destroy_tree(node->left); 
        destroy_tree(node->right); 
        delete node; 
    }
}

// Destructor implementation
BinaryTree::~BinaryTree(){
    destroy_tree(m_root); 
    //m_root = nullptr; 

}

//copy tree method stack overflow
void BinaryTree::copyHelper(BinaryNode* thisNode, BinaryNode* sourceNode) {
    if(sourceNode == nullptr){
        thisNode = nullptr; 
    }
    else{
        //thisNode = new BinaryNode;
        thisNode->value = sourceNode->value;

        if (sourceNode->left != nullptr){
            thisNode->left = new BinaryNode; 
            copyHelper(thisNode->left, sourceNode->left);

        }
        else {
            (thisNode->left = nullptr);

        }

        if (sourceNode->right != nullptr){
            thisNode->right = new BinaryNode; 
            copyHelper(thisNode->right, sourceNode->right);

        }
        else{
            (thisNode->right = nullptr);
        }

    
    }
}

//Copy constructor implementation 
//stack overflow 
BinaryTree::BinaryTree(const BinaryTree &copy){

    if(copy.m_root == nullptr){
       m_root = nullptr; 
   }
    else{
        m_root = new BinaryNode; 
       copyHelper(this->m_root, copy.m_root);
    }

}


// Copy Assignment Constructor
BinaryTree& BinaryTree::operator=(const BinaryTree& rhs){

    if (this != &rhs){
        // Copy the rhs
        BinaryTree temp(rhs);
        // Swap out
        std::swap(temp.m_root, m_root);
    }
    //this = &rhs;
    return *this; 

}


void BinaryTree::Insert(int value, BinaryNode* node){
     //check case 2
     //compare to the node and see if our 'value' is less than or greater
     //than the node
     //This tells us to go left or right in our tree 
    if(value < node->value){
        if(node->left != nullptr){
            Insert(value,node->left); 
        }else{
            //create our new 'leaf node' on the left side of the binary tree
            BinaryNode* newNode = new BinaryNode; 
            newNode->value = value; 
            newNode->left = nullptr; 
            newNode->right = nullptr; 
            //appropriately assign the node 
            node->left = newNode; 
        }
     
    }else if (value >= node ->value){
        if(node->right != nullptr){
            Insert(value, node->right);
        }else{
            BinaryNode* newNode = new BinaryNode; 
            newNode->value = value; 
            newNode->left = nullptr; 
            newNode->right = nullptr; 
            //appropriately assign the node
            node->right = newNode; 

        }

    }

}
void BinaryTree::Insert(int value){
    // TODO:
    // 1: if tree is empty
    if(nullptr==m_root){
        BinaryNode* temp = new BinaryNode; 
        temp->value = value; 
        temp->left = nullptr; 
        temp->right = nullptr; 
        m_root = temp; //assign our root 
    }else{
        Insert(value, m_root);
    }
}



bool BinaryTree::Exists(int value, BinaryNode* node){
    //if null 
    if (node == nullptr){
        return false; 
    }
    //case 2 - we find the node 
    if(node->value == value){
        return true; 
    }
    //case 3 - search left or right for node to see if it exists 
    if (value < node->value){
        return Exists(value,node->left); 
    }
    if (value > node->value){
        return Exists(value, node->right); 
    }
    return false; 
}

bool BinaryTree::Exists(int value){
    return Exists(value, m_root);
}


//printing out the nodes 
void BinaryTree::Print(BinaryNode* node){
    std::cout << node->value << ","; 
    if(node->left != nullptr){
        Print(node->left);
    }
    
    if(node->right != nullptr){
        Print(node->right);
    } 

}

void BinaryTree::Print(){
   Print(m_root);
   std::cout << std::endl; 
}

int BinaryTree::FindReplacement(BinaryNode* node)
{
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->value;
}

void BinaryTree::Remove(BinaryNode* &node, int value){
    //if null 
    if (node == nullptr){
        return; 
    }
    //value less than node 
    if (value < node->value){
        Remove(node->left, value);
    }
    //value greater than node 
    else if (value > node->value){
        Remove(node->right, value);
    }
    else{
        //if left node and right node are null 
        if (node->left == nullptr && node->right == nullptr){
            //delete the node
            delete node; 
            //node is null 
            node = nullptr;
        }
        //otherwise for left and right nodes 
        else if(node->right && node->left){
            //find replacement for right node value 
            int replacementValue = FindReplacement(node->right); 
            Remove(replacementValue);
            node->value = replacementValue;
        }
        else 
        {
            BinaryNode* replacementNode;
            //if right node is null 
            if (node->right == nullptr) {
                //replace left node 
                replacementNode = node->left;
                //otherwise replace right node 
            } else {
                replacementNode = node->right;
            }
            //node equals the replacement node 
            node = replacementNode;
        }
    }
}

void BinaryTree::Remove(int value){
    Remove(m_root, value);
}

int BinaryTree::Sum(BinaryNode* node) {
    if (node == nullptr){
        return 0; 
    }
    return (node->value + Sum(node->left) + Sum(node->right));    
}



int BinaryTree::Sum() {
    return Sum(m_root); 
}


