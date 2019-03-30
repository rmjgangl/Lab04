#include <iostream>
#include <algorithm>
#include <string>
#include "lab4_binary_search_tree.h"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (size == 0) {
        return BinarySearchTree::TaskItem(-1, "N/A");
    } else if (size == 1) {
        int a = root->priority;
        string b = root->description;
        return BinarySearchTree::TaskItem(a, b);
    } else {
        TaskItem* temp = root;
        while (temp->right) {
            temp = temp->right;
        }
        int a = temp->priority;
        string b = temp->description;
        return BinarySearchTree::TaskItem(a, b);
    }
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (size == 0) {
        return BinarySearchTree::TaskItem(-1, "N/A");
    } else if (size == 1) {
        int a = root->priority;
        string b = root->description;
        return BinarySearchTree::TaskItem(a, b);
    } else {
        TaskItem* temp = root;
        while (temp->left) {
            temp = temp->left;
        }
        int a = temp->priority;
        string b = temp->description;
        return BinarySearchTree::TaskItem(a, b);
    }
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
    return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
    TaskItem* exists = new TaskItem(val);
    TaskItem* temp = root;
    
    if (root == NULL)
        return false;
    else if (size == 1 && root->priority == exists->priority)
        return true;
    else if (size == 1 && root->priority != exists->priority)
        return false;
    
    while (temp) {
        if (temp->priority > exists->priority) {
            temp = temp->left;
            if (temp->priority == exists->priority)
                return true;
        } else if (temp->priority < exists->priority) {
            temp = temp->right;
            if (temp->priority == exists->priority)
                return true;
        }
    }
    return false;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
    if (n == NULL)
        return -1;
    else {
        int leftD = get_node_depth(n->left);
        int rightD = get_node_depth(n->right);
        
        if (leftD > rightD)
            return (leftD + 1);
        else
            return (rightD + 1);
    }
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    TaskItem* add = new TaskItem(val);
    TaskItem* temp = root;
    
    if (exists(val))
        return false;
    
    if (root == NULL) {
        temp = add;
        size++;
        return true;
    }
    while (temp) {
        if (add->priority > temp->priority) {
            if (temp->right)
                temp = temp->right;
            else if (!temp->right) {
                temp->right = add;
                size++;
                return true;
            }
        } else if (add->priority < temp->priority) {
            if (temp->left)
                temp = temp->left;
            else if (!temp->left) {
                temp->left = add;
                size++;
                return true;
            }
        }
    }
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {

}
