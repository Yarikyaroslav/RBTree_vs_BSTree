//
// Created by Yaroslav on 15.12.2021.
//

#ifndef TASK5_FINAL_BINT_H
#define TASK5_FINAL_BINT_H

#include "Node.h"

class BinT {
private:
    Node* root;
    Node* search(Node* t, std::string key_);
    void insert(Node* &t, std::string key_);
    void Delete(Node*&p,std::string key_);
    void del(Node* &q,Node* &r);
public:
    BinT():root(nullptr){};
    unsigned long times=0;
    unsigned long size=0;
    Node* search(std::string key_);
    void insert(std::string key_);
    void Delete(std::string key_);
};

Node *BinT::search(std::string key_) {
    return search(root,key_);
}

Node *BinT::search(Node *t, std::string key_) {
    while((t!= nullptr)&&(t->key!=key_)){
        if(t->key<key_)
            t = t->right;
        else
            t = t->left;
    }
    return t;
}

void BinT::insert(std::string key_) {
    insert(root,key_);
}

void BinT::insert(Node *&t, std::string key_) {
    if(t == nullptr){
        t = new Node(key_);
        size++;
    }
    else if(key_ < t->key) {
        times++;
        insert(t->left, key_);
    }
    else if(key_ > t->key) {
        times+=2;
        insert(t->right, key_);
    }
    else {
        t->count++;
        times+=2;
    }
}

void BinT::Delete(std::string key_) {
    Delete(root,key_);
}

void BinT::Delete(Node *&p, std::string key_) {
    if(p== nullptr){}
    else if(key_<p->key){
        Delete(p->left,key_);
    }
    else if(key_>p->key){
        Delete(p->right,key_);
    }
    else{
        auto q = p;
        if(q->right== nullptr)
            p = q->left;
        else if(q->left== nullptr)
            p = q->right;
        else
            del(q,q->left);
    }
}

void BinT::del(Node *&q, Node *&r) {
    if(r->right != nullptr){
        del(q,r->right);
    }
    else{
        q->key = r->key;
        q->count = r->count;
        q = r;
        r = r->left;
    }
}


#endif //TASK5_FINAL_BINT_H
