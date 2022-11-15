//
// Created by Саша on 24.10.2022.
//

#include "Tree.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Tree::add(int value) {
    ///Создание узла дерева
    Node* node = new Node(value);

    ///Если корня нет, то создаём его
    if (!root){
        root = node;
        root->value = value;
        return;
    }

    ///Создание списка для обхода дерева
    ///в ширину для поиска места куда
    ///добавить новый узел списка
    std::list<Node*> list;
    list.push_back(root);
    while (list.front()->right && list.front()->left){
        list.push_back(list.front()->left);
        list.push_back(list.front()->right);
        list.pop_front();
    }

    ///Добавление узла списка
    if (!list.front()->left){
        list.front()->left = node;
    }else{
        list.front()->right = node;
    }
}

void Tree::display(int level, Tree::Node *current) {

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
    cout<<right<<current->value<<endl;

    ///Отрисовка левой ветви
    if (current->left){
        display(level+1, current->left);
    }
}

int Tree::countPositiveNumber() {
    ///Создание списка для обхода дерева в ширину
    std::list<Node*> list;
    list.push_back(root);
    int count = 0;
    while (!list.empty()){
        ///Поиск положительных элементов списка
        if (list.front()->value>0)
            count++;
        if (list.front()->left)
            list.push_back(list.front()->left);
        if (list.front()->right)
            list.push_back(list.front()->right);

        list.pop_front();
    }
    return count;
}

int Tree::count(int value) {
    ///Создание списка для обхода дерева в ширину
    std::list<Node*> list;
    list.push_back(root);
    int count = 0;
    while (!list.empty()){
        ///Поиск элементов равных value
        if (list.front()->value==value)
            count++;
        if (list.front()->left)
            list.push_back(list.front()->left);
        if (list.front()->right)
            list.push_back(list.front()->right);
        list.pop_front();
    }
    return count;
}

void Tree::multX2() {
    ///Создание списка для обхода дерева в ширину
    std::list<Node*> list;
    list.push_back(root);
    while (!list.empty()){
        ///Умножение всех элементов на 2
        list.front()->value*=2;
        if (list.front()->left)
            list.push_back(list.front()->left);
        if (list.front()->right)
            list.push_back(list.front()->right);
        list.pop_front();
    }
}

Tree::Tree(int n) {
    int a[]{-5,-4,-3,-2,-1,0,1,2,3,4,5};
    for (int i=0; i<n; i++){
        add(a[rand()%11]);
    }
}
