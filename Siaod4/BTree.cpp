//
// Created by Саша on 14.11.2022.
//

#include "BTree.h"
#include <string.h>

BTree::BTree(){}

BTree::BTree(char FIO[100], int indx) {
    for (int i=0; i<100; i++){
        this->FIO[i] = FIO[i];
    }
    this->fileIndex = indx;
}

BTree* BTree::insertItem(BTree* root, char FIO[100], int fileIndex) {
    // Добавление корня
    if (!root) {
        return new BTree(FIO, fileIndex);
    }
    // Добавление листа //

    // Вставка в левое поддерево
    if (strcmp(FIO, root->FIO)>0) {
        root->left = insertItem(root->left, FIO, fileIndex);
    }
        // Вставка в правое поддерево
    else if (strcmp(FIO, root->FIO)<0) {
        root->right = insertItem(root->right, FIO, fileIndex);
    }
    return root;
}

BTree* BTree::findItem(BTree* root, char FIO[100])
{
    // Элемента нет в дереве
    if (!root)
        return root;

    // Поиск элемента в дереве
    if (strcmp(root->FIO,FIO)>0) {
        return findItem(root->left, FIO);
    }
    else if (strcmp(root->FIO,FIO)<0) {
        return findItem(root->right, FIO);
    }

    return root;
}

BTree* BTree::deleteItem(BTree* root, char FIO[100])
{
    // Элемента нет в дереве
    if (!root)
        return root;

    // Поиск элемента в дереве
    if (strcmp(root->FIO,FIO)<0) {
        root->left = deleteItem(root->left, FIO);
        return root;
    }
    else if (strcmp(root->FIO,FIO)>0) {
        root->right = deleteItem(root->right, FIO);
        return root;
    }

    // Один потомок
    if (!(root->left)) {
        BTree* temp = root->right;
        delete root;
        return temp;
    }
    else if (!(root->right)) {
        BTree* temp = root->left;
        delete root;
        return temp;
    }

        // Два потомка
    else {
        // Ищем узел для переноса
        BTree* child;
        child = root->left;
        while (child->right) {
            child = child->right;
        }

        // Перенос крайнего узла на место удаляемого
        strcpy(root->FIO, child->FIO);
        root->fileIndex = child->fileIndex;

        // Удаляем перенесенный узел
        root->left = deleteItem(root->left, child->FIO);
        return root;
    }
}

void BTree::display(int level, BTree* current) {
    // Параметры не указаны
    if (!current) {
        return;
    }
    // Расчет отступа
    std::string offset = "";
    for (int i = 0; i < level; i++) {
        offset += "\t\t";
    }
    // Отрисовка правой ветви
    if (current->right) {
        display(level + 1, current->right);
    }
    // Вывод значения узла
    std::cout << offset << "(" << current->FIO <<
    ", " << current->fileIndex << ")" << std::endl;
    // Отрисовка левой ветви
    if (current->left) {
        display(level + 1, current->left);
    }
}
