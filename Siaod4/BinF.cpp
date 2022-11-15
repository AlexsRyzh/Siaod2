//
// Created by Саша on 09.11.2022.
//

#include <cstring>
#include "BinF.h"
#include "RBTree.h"
#include <iostream>
using namespace std;

BinF::BinF(std::string filename) {
    this->filename = filename;
}


void BinF::generateFile(int len) {
    srand(time(NULL));
    ofstream fout("F:\\Siaod\\Siaod4\\file" + to_string(len) + ".bin", ios::out | ios::binary);
    record* x = new record[len];
    for (int i = 0; i < len; i++) {
        strcpy_s(x[i].FIO, ("Surname" + to_string(rand()%100) +
        " Name" + to_string(rand()%100) +
        " Otchestvo" + to_string(rand()%100)).c_str());
        x[i].midScore = rand()%5 + rand()%10*0.1;
        x[i].presence = rand()%2;
        x[i].empty = false;
    }
    fout.write((char*)x, len * sizeof(record));
    fout.close();
}

record BinF::findRecord(char FIO[100], RBTree* rbTree) {
    node* node = rbTree->find(FIO);

    if (node) {
        //×òåíèå çàïèñè èç ôàéëà
        fstream fdirect(filename, ios::binary | ios::out | ios::in);
        record rec;
        fdirect.seekg((node->filedIndex) * sizeof(record), ios::beg);
        fdirect.read((char*)&rec, sizeof(record));

        return rec;
    }
    record rec;
    rec.empty = true;
    return rec;
}

void BinF::changeRecord(record* r, int pos)
{
    fstream fdirect(filename, ios::binary | ios::out | ios::in);
    fdirect.seekg(pos * sizeof(record), ios::beg);
    record temp;
    fdirect.read((char*)&temp, sizeof(record));
    if ((r->empty) || ( strcmp(r->FIO,temp.FIO)==0)) {
        fdirect.seekg(pos * sizeof(record), ios::beg);
        fdirect.write((char*)r, sizeof(record));
    }
    fdirect.close();
}

void BinF::deleteRecord(char FIO[100], RBTree* binTree) {
    record* r = new record();
    r->empty = true;
    node* del = binTree->find(FIO);
    if (del) {
        binTree->remove(FIO);
        changeRecord(r, del->filedIndex);
    }
}