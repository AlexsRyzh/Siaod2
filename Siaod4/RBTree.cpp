//
// Created by Саша on 07.11.2022.
//

#include "RBTree.h"
#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

node::node(color nodeColor,char FIO[100])
: nodeColor(nodeColor) {
    strcpy(this->FIO, FIO);
}

node *RBTree::grandparent(node *n) {
    if ((n != nullptr) && (n->parent != nullptr))
        return n->parent->parent;
    else
        return nullptr;
}

node *RBTree::uncle(node *n){
    node* g = grandparent(n);
    if (g == nullptr)
        return nullptr;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

void RBTree::rotate_left(node *n) {
    node *y = n->right;

    /* establish x->right link */
    n->right = y->left;
    if (y->left != nullptr) y->left->parent = n;

    /* establish y->parent link */
    if (y != n) y->parent = n->parent;
    if (n->parent) {
        if (n == n->parent->left)
            n->parent->left = y;
        else
            n->parent->right = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->left = n;
    if (n != nullptr) n->parent = y;
}

void RBTree::rotate_right(node *n) {
    node *y = n->left;

    /* establish x->left link */
    n->left = y->right;
    if (y->right != nullptr) y->right->parent = n;

    /* establish y->parent link */
    if (y != nullptr) y->parent = n->parent;
    if (n->parent) {
        if (n == n->parent->right)
            n->parent->right = y;
        else
            n->parent->left = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->right = n;
    if (n != nullptr) n->parent = y;
}

void RBTree::insert(char FIO[100], int filexIndex) {
    node* temp = new node(RED,  FIO);
    temp->filedIndex = filexIndex;
    if (root == nullptr){
        root = temp;
    }else{
        node* p = root;
        node* q = nullptr;
        while (p!= nullptr){
            q = p;
            if (strcmp(p->FIO,temp->FIO)<0){
                p = p->right;
            }else{
                p = p->left;
            }
        }
        temp->parent = q;
        if (strcmp(q->FIO,temp->FIO)<0)
            q->right = temp;
        else
            q->left = temp;
    }
    fixInsertion(temp);
}

void RBTree::fixInsertion(node *n) {
    int i =0;
    while (n != nullptr && n != root && n->parent->nodeColor == RED) {
        /* we have a violation */
        if (n->parent == grandparent(n)->left) {
            node *y = uncle(n);
            if (y && y->nodeColor == RED) {
                /* uncle is RED */
                n->parent->nodeColor = BLACK;
                y->nodeColor = BLACK;
                grandparent(n)->nodeColor = RED;
                n = grandparent(n);
            } else {

                /* uncle is BLACK */
                if (n == n->parent->right) {
                    /* make x a left child */
                    n = n->parent;
                    rotate_left(n);
                }
                /* recolor and rotate */
                n->parent->nodeColor = BLACK;
                grandparent(n)->nodeColor = RED;
                rotate_right(grandparent(n));
            }
        } else {

            /* mirror image of above code */
            node *y = grandparent(n)->left;
            if (y && y->nodeColor == RED) {
                /* uncle is RED */
                n->parent->nodeColor = BLACK;
                y->nodeColor = BLACK;
                grandparent(n)->nodeColor = RED;
                n = grandparent(n);
            } else {
                /* uncle is BLACK */
                if (n == n->parent->left) {
                    n= n->parent;
                    rotate_right(n);
                }
                n->parent->nodeColor = BLACK;
                grandparent(n)->nodeColor = RED;
                rotate_left(grandparent(n));
            }
        }
    }
    root->nodeColor = BLACK;
}

void RBTree::remove(char FIO[100]) {
    node* z = root;
    node* y = nullptr;
    node* x = nullptr;

    if (z== nullptr) return;
    // находим узел с ключом key
    while (z->FIO != FIO){
        if (strcmp(z->FIO,FIO)<0)
            z = z->right;
        else
            z = z->left;
    }
    if (z->left == nullptr || z->right == nullptr) {
        /* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y && y->left) y = y->left;
    }

    /* x is y's only child */
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    if (x){
        x->parent = y->parent;
    }

    if (y && y->parent){
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    else{
        root = x;
    }
    if (y != z)strcpy(z->FIO,y->FIO);

    cout<<x;
    if (y->nodeColor == BLACK)
        fixDeleting(x);

    if (y) delete y;

}

void RBTree::fixDeleting(node *n) {
    while (n && n != root && n->nodeColor == BLACK) {
        if (n == n->parent->left) {
            node *w = n->parent->right;
            if (w->nodeColor == RED) {
                w->nodeColor = BLACK;
                n->parent->nodeColor = RED;
                rotate_left(n->parent);
                w = n->parent->right;
            }
            if (w->left->nodeColor == BLACK && w->right->nodeColor == BLACK) {
                w->nodeColor = RED;
                n = n->parent;
            } else {
                if (w->right->nodeColor == BLACK) {
                    w->left->nodeColor = BLACK;
                    w->nodeColor = RED;
                    rotate_right(w);
                    w = n->parent->right;
                }
                w->nodeColor = n->parent->nodeColor;
                n->parent->nodeColor = BLACK;
                w->right->nodeColor = BLACK;
                rotate_left(n->parent);
                n = root;
            }
        } else {
            node *w = n->parent->left;
            if (w->nodeColor == RED) {
                w->nodeColor = BLACK;
                n->parent->nodeColor = RED;
                rotate_right(n->parent);
                w = n->parent->left;
            }
            if (w->right->nodeColor== BLACK && w->left->nodeColor == BLACK) {
                w->nodeColor = RED;
                n = n->parent;
            } else {
                if (w->left->nodeColor == BLACK) {
                    w->right->nodeColor = BLACK;
                    w->nodeColor = RED;
                    rotate_left(w);
                    w = n->parent->left;
                }
                w->nodeColor = n->parent->nodeColor;
                n->parent->nodeColor = BLACK;
                w->left->nodeColor = BLACK;
                rotate_right(n->parent);
                n = root;
            }
        }
    }
    if (n) n->nodeColor = BLACK;
}

void RBTree::display(int level, node *current) {

    ///Параметры не указаны
    if ((!current) && (level == 0)){
        display(level, this->root);
        return;
    }

    ///Отрисовка левой ветви
    if (current->right){
        display(level+1, current->right);
    }

    ///Вывод значения узла
    cout.width(4*level);
    cout<<right<<"( "<<current->FIO<<" "<<current->filedIndex<<" )"<<endl;

    ///Отрисовка левой ветви
    if (current->left){
        display(level+1, current->left);
    }
}

void RBTree::displayColor(int level,node *current) {

    ///Параметры не указаны
    if ((!current) && (level == 0)){
        displayColor(level, this->root);
        return;
    }

    ///Отрисовка левой ветви
    if (current->right){
        displayColor(level+1, current->right);
    }

    ///Вывод значения узла
    cout.width(4*level);
    cout<<right<<current->nodeColor<<endl;

    ///Отрисовка левой ветви
    if (current->left){
        displayColor(level+1, current->left);
    }
}

node* RBTree::find(char FIO[100]){
    node* z = root;
    while (z && strcmp(z->FIO,FIO)!=0){
        if (strcmp(z->FIO,FIO)<0)
            z = z->right;
        else
            z = z->left;
    }
    return z;
}