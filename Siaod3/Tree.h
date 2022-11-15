//
// Created by Саша on 24.10.2022.
//

#ifndef SIAOD_TREE_H
#define SIAOD_TREE_H
#include <list>

class Tree {

    ///Структура узла дерева
    class Node{
    public:
        int value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int value){
            this->value=value;
        }
    };

    Node* root = nullptr;
public:

    Tree(int n);

    ///Добавление элемента в дерево
    void add(int value);
    ///Вывод дерева на экран
    void display(int level = 0, Node* current = nullptr);
    ///Подсчёт количества положительных элементов
    int countPositiveNumber();
    ///Подсчёт количества элементов равных (value)
    int count(int value);
    ///Умножение всех элементов дерева на 2
    void multX2();
};


#endif //SIAOD_TREE_H
