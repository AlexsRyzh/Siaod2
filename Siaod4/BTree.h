#ifndef SIAOD_BTREE_H
#define SIAOD_BTREE_H
#include <iostream>

class BTree {
        char FIO[100];
        int fileIndex;
        BTree* left = nullptr;
        BTree* right = nullptr;
    public:
        BTree();
        BTree(char FIO[100], int indx);
        int getIndex() {
            return this->fileIndex;
        }
        void setRight(BTree* right) {
            this->right = right;
        }
        void setLeft(BTree* left) {
            this->left = left;
        }
        // Добавление узла
        BTree* insertItem(BTree* root, char FIO[100], int fileIndex);
        // Поиск узла в дереве
        BTree* findItem(BTree* root, char FIO[100]);
        // Удаление узла из дерева
        BTree* deleteItem(BTree* root, char FIO[100]);
        // Вывод дерева на экран
        void display(int level = 0, BTree* current = nullptr);
};
#endif //SIAOD_BTREE_H
