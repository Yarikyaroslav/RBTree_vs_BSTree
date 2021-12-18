//
// Created by Yaroslav on 15.12.2021.
//

#ifndef TASK5_FINAL_NODE_H
#define TASK5_FINAL_NODE_H


struct Node {
    std::string key;
    unsigned count;
    Node* left;
    Node* right;
    explicit Node(std::string key_): key(key_),count(1),left(nullptr),right(nullptr){};
};


#endif //TASK5_FINAL_NODE_H
