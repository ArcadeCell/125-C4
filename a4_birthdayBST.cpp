#include "a4_birthdayBST.hpp"

BirthdayBST::BirthdayBST(){
    root = nullptr;
    size = 0;
}

int BirthdayBST::getSize(){
    return size;
}

void BirthdayBST::insertNode(Birthday* value) {
    root = insertNode_rec(root, value);
}

Birthday* BirthdayBST::removeNode(Birthday* value){
    BirthdayBSTreeNode* node = findNodeByYMDN_rec(root, value->year,
    value->month, value->day, value->name);
    if (node == nullptr) return nullptr;
    root = removeNode_rec(root, value);
    size--;
    return node->value;
}

Birthday* BirthdayBST::findNodeByMD(short month, short day){
    BirthdayBSTreeNode* node = findNodeByMD_rec(root, month, day);
    if (node == nullptr) return nullptr;
    return node->value;
}

void BirthdayBST::printAllNodeWithMatchingMD(short month, short day, ostream& os){
    printAllNodeWithMatchingMD_rec(root, os, month, day);
}

void BirthdayBST::inOrderPrint(ostream& os){
    inOrderPrint_rec(root, os);
}

BirthdayBST::~BirthdayBST(){
    root = nullptr;
    deleteTree_rec(root);
}
