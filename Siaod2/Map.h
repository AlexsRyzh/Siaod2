#ifndef SIAOD_MAP_H
#define SIAOD_MAP_H
#include<vector>
#include<list>
#include <string>

using namespace std;

class Map {
    class Node{
    public:
        string key;
        int fileIndex;
        Node(string key, int fileIndex){
            this->key = key;
            this->fileIndex = fileIndex;
        }
    };
    int cap;
    double load;
    vector<list<Node>> table;
    int size = 0;
    // Хеш-функция, вычисляющая хеш-код для элемента
    int hash(string key);
public:
    Map(int cap);  // Конструктор класса
    // Возвращает позицию (индекс) элемента в таблице
    int findItem(string key);
    // Добавляет значение в таблицу
    void insertItem(string x, int fileIndex);
    // Удаляет значение из таблицы и возвращает позицию данных в файле
    int deleteItem(string key);
    // Вывод хеш-таблицы
    void displayHash();
    // Метод рехеширования. При вызове увеличивает размер таблицы вдвое
    void reHash();
    int getSize(){
        return size;
    }
};


#endif //SIAOD_MAP_H
