#ifndef SIAOD_RBTREE_H
#define SIAOD_RBTREE_H
enum color {
    RED,
    BLACK
};
struct node{
    node* parent = nullptr;
    node* left = nullptr;
    node* right = nullptr;
    color nodeColor;
    char FIO[100];
    int filedIndex;
    node(color nodeColor,char FIO[100]);
};
class RBTree {
    node* root = nullptr;
private:
    node* grandparent(node* n);
    node* uncle(node* n);
    void rotate_left(node* n);
    void rotate_right(node* n);
    void fixInsertion(node* n);
    void fixDeleting(node* n);
public:
    void insert(char FIO[100], int filexIndex);
    void remove(char FIO[100]);
    node* find(char FIO[100]);
    ///Вывод дерева на экран
    void display(int level = 0, node* current = nullptr);
    void displayColor(int level = 0, node* current = nullptr);
};
#endif //SIAOD_RBTREE_H
