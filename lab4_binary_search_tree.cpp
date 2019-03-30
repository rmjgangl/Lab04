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
    delete root;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (root == NULL) {
        return BinarySearchTree::TaskItem(-1, "N/A");
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
    if (root == NULL) {
        return BinarySearchTree::TaskItem(-1, "N/A");
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
    
    while (temp->left || temp->right) {
        if (temp->priority == exists->priority)
            return true;
        else if (temp->priority > exists->priority) {
            if (!temp->left)
                return false;
            temp = temp->left;
        } else if (temp->priority < exists->priority) {
            if (!temp->right)
                return false;
            temp = temp->right;
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
        root = temp;
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
    /*TaskItem* remove = new TaskItem(val);
    TaskItem* temp = root;
    
    if (!exists(val))
        return false;
    

    return true;*/
    
    if (root == NULL) {
        return false;
    }
    TaskItem *del = new TaskItem(val);
    TaskItem *tester = root;
    TaskItem *parent = root;
    while (tester != NULL) {
        if (del->priority < tester->priority && tester->left != NULL) {
            parent = tester;
            tester = tester->left;
        } else if (del->priority > tester->priority && tester->right != NULL) {
            parent = tester;
            tester = tester->right;
        } else {
            break;
        }
    }
    //tester is the node that will be deleted
    if (tester->priority != del->priority) {
        return false;
    }
    //1. Node being deleted is leaf node
    if (tester->left == NULL && tester->right == NULL) {
        //delete that node directly
        size--;
        if (del->priority == root->priority) {
            root = NULL; //potential memory issues here
        } else if (del->priority < parent->priority) {
            parent->left = NULL;
        }
        else if (del->priority > parent->priority) {
            parent->right = NULL;
        }
        delete tester;
        //tester = NULL;
        //delete del;
        //delete parent;
        return true;
    }
    
    //2. Node being deleted has one child
    //Create a temp pointer to the node being deleted
    //link the parent node to the child node
    //delete the node pointed to by the temporary pointer
    if (tester->left != NULL && tester->right == NULL) {
        if (del->priority == root->priority) {
            root = root->left; //potential memory issues here
        } else if (del->priority < parent->priority) {
            parent->left = tester->left;
        } else if (del->priority > parent->priority) {
            parent->right = tester->left;
        }
        delete tester;
        //delete del;
        //delete parent;
        size--;
        return true;
    }
    else if (tester->right != NULL && tester->left == NULL) {
        if (del->priority == root->priority) {
            root = root->right; //potential memory issues here
        } else if (del->priority < parent->priority) {
            parent->left = tester->right;
        } else if (del->priority > parent->priority) {
            parent->right = tester->right;
        }
        delete tester;
        //delete del;
        //delete parent;
        size--;
        return true;
    }
    //3. Node being deleted has 2 children
    //find min of right subtree, copy that value
    TaskItem *temp = tester->right; //tester is the root
    while (temp->left != NULL) {
        temp = temp->left;
    }
    //temp now has the minimum value
    
    //replace node to be deleted with that value
    //delete the node that you took the min value from
    if (del->priority == root->priority) {
        remove(*temp);
        root->priority = temp->priority;
        root->description = temp->description;
        size--;
        return true;
    } else if (del->priority < parent->priority) {
        remove(*temp);
        parent->left->priority = temp->priority;
        size--;
        return true;
    } else if (del->priority > parent->priority) {
        remove(*temp);
        parent->right->priority = temp->priority;
        size--;
        return true;
    }
    return true;
}
