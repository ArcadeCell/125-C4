#ifndef A4_BIRTHDAYBST_HPP
#define A4_BIRTHDAYBST_HPP

#include "a4_birthdaylib.hpp"

#include <string>
#include <iostream>

//use a combination of struct and class
//for simple things like a node we keep it as struct
typedef struct node {
    Birthday* value;
    struct node* left;
    struct node* right;
    struct node* parent;    
} BirthdayBSTreeNode;
    
class BirthdayBST {
    private:
        BirthdayBSTreeNode* root;
        int size; //keep track of the size of the tree

        //internal recursive insert function
        BirthdayBSTreeNode* insertNode_rec(BirthdayBSTreeNode* node, Birthday* value) {
            // if the tree is empty, create a new node
            if (node == nullptr) {
                BirthdayBSTreeNode* new_node = newNode(value);
                return new_node;
            }
            // if the tree is not empty, compare the value to the root
            // inserted by month-day-year-name
            // compare months
            if (value->month < node->value->month){
                node->left = insertNode_rec(node->left, value);
                node->left->parent = node;
            }
            else if (value->month > node->value->month){
                node->right = insertNode_rec(node->right, value);
                node->right->parent = node;
            }
            else{
                // same month, compare days
                if (value->day < node->value->day){
                    node->left = insertNode_rec(node->left, value);
                    node->left->parent = node;
                } 
                else{
                    node->right = insertNode_rec(node->right, value);
                    node->right->parent = node;
                }
            }
            return node;
        }
        //internal recursive remove function
        BirthdayBSTreeNode* removeNode_rec(BirthdayBSTreeNode* node,
                                        Birthday* value){
            // no matching birthday found
            if (node == nullptr) return nullptr;
            // compare months
            if (value->month < node->value->month)
                node->left = removeNode_rec(node->left, value);
            else if (value->month > node->value->month)
                node->right = removeNode_rec(node->right, value);
            else{
                // same month, compare days
                if (value->day < node->value->day)
                    node->left = removeNode_rec(node->left, value);
                else if (value->day > node->value->day)
                    node->right = removeNode_rec(node->right, value);
                else{
                    // same month and day, compare years
                    if (value->year < node->value->year)
                        node->left = removeNode_rec(node->left, value);
                    else if (value->year > node->value->year)
                        node->right = removeNode_rec(node->right, value);  
                    else{
                        // same date, compare names
                        if (value->name < node->value->name)
                            node->left = removeNode_rec(node->left, value);
                        else if (value->name > node->value->name)
                            node->right = removeNode_rec(node->right, value);
                        else{
                            // Same birthday, delete the node
                            if (node->left == nullptr){
                                BirthdayBSTreeNode* temp = node->right;
                                delete node;
                                return temp;
                                            }
                            else if (node->right == nullptr){
                                BirthdayBSTreeNode* temp = node->left;
                                delete node;
                                return temp;
                            }
                            // node with two children, get the inorder successor
                            BirthdayBSTreeNode* temp = minSuccessor(node->right);
                            // store the inorder successor's value
                            node->value = temp->value;
                            // delete the inorder successor
                            node->right = removeNode_rec(node->right, temp->value);
                        }
                    }
                }
            }
            return node;
        }
        //internal recursive find function for duplicates, useful for insert
        BirthdayBSTreeNode* findNodeByYMDN_rec(BirthdayBSTreeNode* node,
        short year, short month, short day, string name){
            // no matching birthday found
            if (node == nullptr) return nullptr;
            if (node->value->year == year && node->value->month == month &&
            node->value->day == day && node->value->name == name)
                return node;
            // compare months
            if (node->value->month < month)
                return findNodeByYMDN_rec(node->right, year, month, day, name);
            else if (node->value->month > month)
                return findNodeByYMDN_rec(node->left, year, month, day, name);
            else{
                // same month, compare days
                if (node->value->day < day)
                    return findNodeByYMDN_rec(node->right, year, month, day, name);
                else if (node->value->day > day)
                    return findNodeByYMDN_rec(node->left, year, month, day, name);
                else{ 
                    // same month and day, compare years
                    if (node->value->year < year)
                        return findNodeByYMDN_rec(node->right, year, month, day, name);
                    else if (node->value->year > year)
                        return findNodeByYMDN_rec(node->left, year, month, day, name);   
                    else{
                        // same date, compare names
                        if (node->value->name < name)
                            return findNodeByYMDN_rec(node->right, year, month, day, name);
                        else
                            return findNodeByYMDN_rec(node->left, year, month, day, name);
                    }
                }
            }
        }
        //internal recursive find function for same month and day, useful for remove
        BirthdayBSTreeNode* findNodeByMD_rec(BirthdayBSTreeNode* node, short month, short day){
            if (node == nullptr) return nullptr;
            if (node->value->month == month && node->value->day == day)
                return node;
            if (node->value->month < month)
                return findNodeByMD_rec(node->right, month, day);
            else if (node->value->month > month)
                return findNodeByMD_rec(node->left, month, day);
            else{
                if (node->value->day < day)
                    return findNodeByMD_rec(node->right, month, day);
                else
                    return findNodeByMD_rec(node->left, month, day);
            }
        }       
        //internal recursive print function with matching month and day
        void printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, 
        ostream& os, short month, short day){
            if (node == nullptr) return;
            // print user inorder traversal
            printAllNodeWithMatchingMD_rec(node->left, os, month, day); 
            if (node->value->month == month && node->value->day == day)
                print_Birthday(node->value, os);
            printAllNodeWithMatchingMD_rec(node->right, os, month, day);
        }
        //internal recursive print function performing an in-order traversal
        void inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os){
            if (node == nullptr) return;
            // print user inorder traversal
            inOrderPrint_rec(node->left, os);
            print_Birthday(node->value, os);
            inOrderPrint_rec(node->right, os);
        }
        //internal recursive delete function releasing memory use by the tree
        //also releases the Birthday structs along the way
        void deleteTree_rec(BirthdayBSTreeNode* node){
            if (node == nullptr) return;
            deleteTree_rec(node->left);
            deleteTree_rec(node->right);
            delete node->value;
            delete node;
        }
        //internal helper function for creating a new tree node
        BirthdayBSTreeNode* newNode(Birthday* value){
            BirthdayBSTreeNode* new_node = new BirthdayBSTreeNode;
            new_node -> value = value;
            new_node -> left = nullptr;
            new_node -> right = nullptr;
            new_node -> parent = nullptr;
            return new_node;
        }
        //internal helper function for finding the minimal successor, used by remove
        BirthdayBSTreeNode* minSuccessor(BirthdayBSTreeNode* node){
            BirthdayBSTreeNode* current = node;
            while (current->left != nullptr){
                current = current->left;
            }
            return current;
        }
        
    public:
        //constructor
        BirthdayBST();
        //return the size of the tree
        int getSize();
        //insert the Birthday entry to the tree
        void insertNode(Birthday* value);
        //remove a node with matching content from the tree, return the data
        Birthday* removeNode(Birthday* value);
        //find a node with matching year, month, day, and name, return the data
        Birthday* findNodeByYMDN(short year, short month, short day,
                                string name);
        //find a matching node with month and date, return the data
        Birthday* findNodeByMD(short month, short day);
        //print all content with matching node with month and day
        void printAllNodeWithMatchingMD(short month, short day, ostream& os);
        //performs an in-order traversal and print the content to the output stream
        void inOrderPrint(ostream& os);
        //destructor
        ~BirthdayBST();
};

    #endif