#include "a4_birthdayBST.hpp"

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

BirthdayBSTreeNode* findNodeByYMDN_rec(BirthdayBSTreeNode* node,
short year, short month, short day, string name){
    if (node == NULL) return NULL;
    if (node->value->year == year && node->value->month == month &&
        node->value->day == day && node->value->name == name)
        return node;
    return node;
}

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

void printAllNodeWithMatchingMD_rec(BirthdayBSTreeNode* node, 
ostream& os, short month, short day){
    if (node == NULL) return;
    printAllNodeWithMatchingMD_rec(node->left, os, month, day); 
    if (node->value->month == month && node->value->day == day)
        print_Birthday(node->value, os);
    printAllNodeWithMatchingMD_rec(node->right, os, month, day);
}

void inOrderPrint_rec(BirthdayBSTreeNode* node, ostream& os){
    if (node == NULL) return;
    inOrderPrint_rec(node->left, os);
    print_Birthday(node->value, os);
    inOrderPrint_rec(node->right, os);
}

void deleteTree_rec(BirthdayBSTreeNode* node){
    if (node == NULL) return;
    deleteTree_rec(node->left);
    deleteTree_rec(node->right);
    delete node->value;
    delete node;
}

BirthdayBSTreeNode* newNode(Birthday* value){
    BirthdayBSTreeNode* new_node = new BirthdayBSTreeNode;
    new_node -> value = value;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> parent = NULL;
    return new_node;
}

BirthdayBSTreeNode* minSuccessor(BirthdayBSTreeNode* node){
    BirthdayBSTreeNode* current = node;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

BirthdayBST::BirthdayBST(){
    root = NULL;
    size = 0;
}

int BirthdayBST::getSize(){
    return size;
}

void BirthdayBST::insertNode(Birthday* value) {
    root = insertNode_rec(root, value);
}

Birthday* BirthdayBST::findNodeByMD(short month, short day){
    BirthdayBSTreeNode* node = findNodeByMD_rec(root, month, day);
    if (node == NULL) return NULL;
    return node->value;
}

void BirthdayBST::printAllNodeWithMatchingMD(short month, short day, ostream& os){
    printAllNodeWithMatchingMD_rec(root, os, month, day);
}

void BirthdayBST::inOrderPrint(ostream& os){
    inOrderPrint_rec(root, os);
}

BirthdayBST::~BirthdayBST(){
    deleteTree_rec(root);
}
