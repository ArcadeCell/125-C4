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
            BirthdayBSTreeNode* insertNode_rec(BirthdayBSTreeNode* node, Birthday* value);
            //internal recursive remove function
            BirthdayBSTreeNode* removeNode_rec(BirthdayBSTreeNode* node,
                                            Birthday* value);
            //internal recursive find function for duplicates, useful for insert
            BirthdayBSTreeNode* findNodeByYMDN_rec(BirthdayBSTreeNode* node,
            short year, short month, short day, string name);
            //internal recursive find function for same month and day, useful for remove
            BirthdayBSTreeNode* findNodeByMD_rec(BirthdayBSTreeNode* node,
                                            short month, short day);
            //internal recursive print function with matching month and day
            void printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, ostream& os,
                                            short month, short day);
            //internal recursive print function performing an in-order traversal
            void inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os);
            //internal recursive delete function releasing memory use by the tree
            //also releases the Birthday structs along the way
            void deleteTree_rec(BirthdayBSTreeNode* node);
            //internal helper function for creating a new tree node
            BirthdayBSTreeNode* newNode(Birthday* value);
            //internal helper function for finding the minimal successor, used by remove
            BirthdayBSTreeNode* minSuccessor(BirthdayBSTreeNode* node);
            
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