//
// Created by Yaroslav on 15.12.2021.
//

#ifndef TASK5_FINAL_RBTNODE_H
#define TASK5_FINAL_RBTNODE_H

enum RBTColor { Black, Red };

struct  RBTNode
{
    std::string key;
    unsigned count;
    RBTColor color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    RBTNode(std::string k, RBTColor c, RBTNode* p, RBTNode*l, RBTNode*r) :
            key(k),count(1), color(c), parent(p), left(l), right(r) {};
};

#endif //TASK5_FINAL_RBTNODE_H
