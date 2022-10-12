#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(int cap)
{
    this->cap=cap;
    this->load = 0.0;
    this->table = vector<list<Node>>(cap);
}


int Map::hash(string key) {
    return (((int)key[0])+(int)key[key.size()-1])%cap;
}


int Map::findItem(string key)
{
    // получаем индекс элемента в таблице
    int index = hash(key);

    for (Node item: table[index]){
        if (item.key==key){
            return item.fileIndex;
        }
    }
    return -1;
}


void Map::insertItem(string const key, int const fileIndex)
{
    int index = hash(key);
    table[index].push_back(Node(key, fileIndex));
    this->load = (double)(load * cap + 1) / cap;
    if (this->load > 0.75) {
        reHash();
    }
    size++;
}

int Map::deleteItem(string key)
{
    // get the hash index of key
    int index = hash(key);
    int fileIndex = -1;
    // find the key in (index)th list
    for (auto iter = table[index].begin();
         iter != table[index].end(); iter++) {
        if (iter->key == key){
            fileIndex = iter->fileIndex;
            table[index].erase(iter);
            break;
        }
    }
    if (fileIndex!=-1){
        this->load = (double)(load * cap - 1) / cap;
        size--;
    }
    return fileIndex;

}


void Map::displayHash() {
    for (int i = 0; i < cap; i++) {
        cout<<i<<": "<<endl;
        for (Node& listItem : table[i]){
            cout<<"   { key = "<<listItem.key<<", fileIndex = "<<listItem.fileIndex<<" }\n";
        }
    }
    cout << "Load: " << this->load << endl;
}

void Map::reHash() {
    cout << "*Rehashing*" << endl;
    vector<list<Node>> small = table;
    this->cap *= 2;
    this->table = vector<list<Node>>(cap);
    this->load = 0.0;
    this->size = 0;
    for (auto& list: small){
        for (auto& item: list){
            insertItem(item.key, item.fileIndex);
        }
    }
}