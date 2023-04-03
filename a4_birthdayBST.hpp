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
                // If the tree is empty, create a new node as the root
                if (node == NULL) {
                    BirthdayBSTreeNode* new_node = new BirthdayBSTreeNode;
                    new_node->value = value;
                    new_node->left = NULL;
                    new_node->right = NULL;
                    new_node->parent = NULL;
                    return new_node;
                }
                // If the tree is not empty, compare the value to the root
                // If the value is less than the root, insert it to the left
                if (value->month < node->value->month) {
                    node->left = insertNode_rec(node->left, value);
                    node->left->parent = node;
                }
                // If the value is greater than the root, insert it to the right
                else if (value->month > node->value->month) {
                    node->right = insertNode_rec(node->right, value);
                    node->right->parent = node;
                }
                else{
                    // Same month, compare days
                    if (value->day < node->value->day) {
                        node->left = insertNode_rec(node->left, value);
                        node->left->parent = node;
                    } else {
                        node->right = insertNode_rec(node->right, value);
                        node->right->parent = node;
                    }
                }
                return node;
            }
            //internal recursive remove function
            BirthdayBSTreeNode* removeNode_rec(BirthdayBSTreeNode* node,
                                            Birthday* value);
            //internal recursive find function for duplicates, useful for insert
            BirthdayBSTreeNode* findNodeByYMDN_rec(BirthdayBSTreeNode* node,
            short year, short month, short day, string name){
                if (node == NULL) return NULL;
                if (node->value->year == year && node->value->month == month &&
                    node->value->day == day && node->value->name == name)
                    return node;
                return node;
            }
            //internal recursive find function for same month and day, useful for remove
            BirthdayBSTreeNode* findNodeByMD_rec(BirthdayBSTreeNode* node, short month, short day){
                if (node == NULL) return NULL;
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
                if (node == NULL) return;
                printAllNodeWithMatchingMD_rec(node->left, os, month, day); 
                if (node->value->month == month && node->value->day == day)
                    print_Birthday(node->value, os);
                printAllNodeWithMatchingMD_rec(node->right, os, month, day);
            }
            //internal recursive print function performing an in-order traversal
            void inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os){
                if (node == NULL) return;
                inOrderPrint_rec(node->left, os);
                print_Birthday(node->value, os);
                inOrderPrint_rec(node->right, os);
            }
            //internal recursive delete function releasing memory use by the tree
            //also releases the Birthday structs along the way
            void deleteTree_rec(BirthdayBSTreeNode* node){
                if (node == NULL) return;
                deleteTree_rec(node->left);
                deleteTree_rec(node->right);
                delete node->value;
                delete node;
            }
            //internal helper function for creating a new tree node
            BirthdayBSTreeNode* newNode(Birthday* value){
                BirthdayBSTreeNode* new_node = new BirthdayBSTreeNode;
                new_node -> value = value;
                new_node -> left = NULL;
                new_node -> right = NULL;
                new_node -> parent = NULL;
                return new_node;
            }
            //internal helper function for finding the minimal successor, used by remove
            BirthdayBSTreeNode* minSuccessor(BirthdayBSTreeNode* node){
                BirthdayBSTreeNode* current = node;
                while (current->left != NULL){
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