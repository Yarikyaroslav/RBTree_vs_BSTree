//
// Created by Yaroslav on 15.12.2021.
//

#ifndef TASK5_FINAL_RBTREE_H
#define TASK5_FINAL_RBTREE_H

#include <set>
#include"RBTNode.h"

class  RBTree
{
public:
    unsigned long t=0;
    unsigned long size=0;
    RBTree();
    ~RBTree();

    void insert(std::string key);    // Вставляем узел, ключ это значение ключа, внешний интерфейс
    void remove(std::string key); // Удалить ключевой узел
    RBTNode* search(std::string key);
    std::set<unsigned> getSet();

private:
    void leftRotate(RBTNode* &root, RBTNode* x);// левая рука
    void rightRotate(RBTNode* &root, RBTNode* y);// правая рука

    void insert(RBTNode* &root, RBTNode* node);// Вставляем узел, внутренний интерфейс
    void InsertFixUp(RBTNode* &root, RBTNode* node);
    void destroy(RBTNode* &node);

    void remove(RBTNode*& root, RBTNode*node);// Удалить узел как KEY
    void removeFixUp(RBTNode* &root, RBTNode* node, RBTNode*parent);

    RBTNode* search(RBTNode*node, std::string key) const;

    void prohod(std::set<unsigned>& s, RBTNode* n);
private:
    RBTNode*root;
};

//Конструктор
RBTree::RBTree() :root(nullptr) {
}
// Деструктор
RBTree::~RBTree() {
    destroy(root);
}

void RBTree::leftRotate(RBTNode* &root, RBTNode* x) {
    RBTNode*y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
};
//Правая рука
void RBTree::rightRotate(RBTNode*&root, RBTNode* y) {
    RBTNode*x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else {
        if  (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
};
// вставка
void RBTree::insert(std::string key)
{
    RBTNode*z = new RBTNode(key, Red, nullptr, nullptr, nullptr);
    insert(root, z);
};

void RBTree::insert(RBTNode* &root, RBTNode* node)
{
    RBTNode *x = root;
    RBTNode *y = nullptr;
    while (x != nullptr){
        y = x;
        if (node->key > x->key) {
            x = x->right;
            t++;
        }
        else if(node->key < x->key) {
            x = x->left;
            t+=2;
        }
        else {
            t+=2;
            x->count++;
            break;
        }
    }
    if(x == nullptr) {
        size++;
        node->parent = y;
        if (y != nullptr) {
            if (node->key > y->key) {
                t++;
                y->right = node;
            }
            else{
                t++;
                y->left = node;
            }
        }
        else
            root = node;
        node->color = Red;
        InsertFixUp(root, node);
    }
};

void RBTree::InsertFixUp(RBTNode* &root, RBTNode* node)
{
    RBTNode*parent;
    parent = node->parent;
    while (node != RBTree::root  && parent->color == Red){
        RBTNode*gparent = parent->parent;
        if (gparent->left == parent){
            RBTNode*uncle = gparent->right;
            if (uncle != nullptr && uncle->color == Red){
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            }
            else{
                if (parent->right == node){
                    leftRotate(root, parent);
                    std::swap(node, parent);
                }
                rightRotate(root, gparent);
                gparent->color = Red;
                parent->color = Black;
                break;
            }
        }
        else{
            RBTNode*uncle = gparent->left;
            if (uncle != nullptr && uncle->color == Red)
            {
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            }
            else
            {
                if (parent->left == node){
                    rightRotate(root, parent);
                    std::swap(parent, node);
                }
                leftRotate(root, gparent);
                parent->color = Black;
                gparent->color = Red;
                break;
            }
        }
    }
    root->color = Black;
}

// Уничтожить красные и черные деревья
void RBTree::destroy(RBTNode* &node)
{
    if (node == nullptr)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}

void RBTree::remove(std::string key)
{
    RBTNode*deletenode = search(root,key);
    if (deletenode != nullptr)
        remove(root, deletenode);
}

void RBTree::remove(RBTNode*&root, RBTNode*node)
{
    RBTNode *child, *parent;
    RBTColor color;
    // Левый и правый узлы удаленного узла не пусты (не конечные узлы)
    if (node->left != nullptr && node->right != nullptr)
    {
        RBTNode *replace = node;
        // Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
        replace = node->right;
        while (replace->left != nullptr)
        {
            replace = replace->left;
        }
        // Случай, когда удаленный узел не является корневым узлом
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
            // Ситуация с корневым узлом
        else
            root = replace;
        // child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
        // Поскольку замена является преемником, он не может иметь левого дочернего узла
        // Аналогично, у узла-предшественника не может быть правого дочернего узла
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        // Удаленный узел является родительским узлом замещающего узла (repalce)
        if (parent == node)
            parent = replace;
        else
        {
            // Существование дочернего узла
            if (child != nullptr)
                child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == Black)
            removeFixUp(root, child, parent);

        delete node;
        return;
    }
    // Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
    if (node->left != nullptr)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;
    if (child)
    {
        child->parent = parent;
    }
    // Удаленный узел не является корневым узлом
    if (parent)
    {
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
        // Удаленный узел является корневым узлом
    else
        RBTree::root = child;

    if(RBTree::root != nullptr) {
        if (color == Black) {
            removeFixUp(root, child, parent);
        }
    }
    delete node;

}

void RBTree::removeFixUp(RBTNode* &root, RBTNode* node,RBTNode*parent)
{
    RBTNode*othernode;
    while ((node == nullptr) || node->color == Black && node != RBTree::root)
    {
        if (parent->left == node)
        {
            othernode = parent->right;
            if (othernode->color == Red)
            {
                othernode->color = Black;
                parent->color = Red;
                leftRotate(root, parent);
                othernode = parent->right;
            }
            else
            {
                if (!(othernode->right) || othernode->right->color == Black)
                {
                    othernode->left->color=Black;
                    othernode->color = Red;
                    rightRotate(root, othernode);
                    othernode = parent->right;
                }
                othernode->color = parent->color;
                parent->color = Black;
                othernode->right->color = Black;
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            othernode = parent->left;
            if (othernode->color == Red)
            {
                othernode->color = Black;
                parent->color = Red;
                rightRotate(root, parent);
                othernode = parent->left;
            }
            if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
            {
                othernode->color = Red;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!(othernode->left) || othernode->left->color == Black)
                {
                    othernode->right->color = Black;
                    othernode->color = Red;
                    leftRotate(root, othernode);
                    othernode = parent->left;
                }
                othernode->color = parent->color;
                parent->color = Black;
                othernode->left->color = Black;
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        node->color = Black;
}

RBTNode* RBTree::search(std::string key)
{
    return search(root, key);
}

RBTNode* RBTree::search(RBTNode*node, std::string key) const
{
    if (node == nullptr || node->key == key)
        return node;
    else
    if (key > node->key)
        return search(node->right, key);
    else
        return search(node->left, key);
}

void RBTree::prohod(std::set<unsigned int> &s, RBTNode *n) {
    s.insert(n->count);
    if(n->left!= nullptr){
        prohod(s,n->left);
    }
    if(n->right!= nullptr){
        prohod(s,n->right);
    }
}


std::set<unsigned> RBTree::getSet() {
    std::set<unsigned> ans;
    prohod(ans,root);
    return ans;
}


#endif //TASK5_FINAL_RBTREE_H
