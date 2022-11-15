//
// Created by Саша on 09.11.2022.
//

#ifndef SIAOD_BINF_H
#define SIAOD_BINF_H
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "RBTree.h"
#include "BTree.h"

struct record {
    char FIO[100];
    double midScore;
    bool presence;
    bool empty = false;
};

class BinF {
    std::string filename;
public:
    BinF(std::string);
    void generateFile(int len);
    record findRecord(char FIO[100], RBTree* binTree);
    void changeRecord(record*, int pos);
    void deleteRecord(char FIO[100],RBTree* binTree);
};

#endif //SIAOD_BINF_H
