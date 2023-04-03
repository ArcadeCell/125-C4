#include "a4_birthdayBST.hpp"

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
