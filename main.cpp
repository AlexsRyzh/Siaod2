#include <iostream>
#include<fstream>
#include<string>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include "Siaod4/BTree.h"
#include "Siaod4/RBTree.h"
#include "Siaod4/BinF.h"

using namespace std;

string filename = "F:\\Siaod\\Siaod4\\file15.bin";


//record findRecord(int key, AVLTree* binTree) {
//    AVLTree* node = binTree->findNode(key, binTree);
//
//    if (node) {
//        //?????? ?????? ?? ?????
//        fstream fdirect(filename, ios::binary | ios::out | ios::in);
//        record rec;
//        fdirect.seekg((node->getIndex()) * sizeof(record), ios::beg);
//        fdirect.read((char*)&rec, sizeof(record));
//
//        return rec;
//    }
//    record rec;
//    rec.empty = true;
//    return rec;
//}



void operator<<(ostream& stream, const record r) {
    cout << r.FIO << " " << r.midScore << " " << r.presence << endl;
}

int main() {

    BinF binFile = BinF(filename);
//    binFile.generateFile(15);


    RBTree* rbTree = new RBTree();
    int fileIndex = 0;
    ifstream fin(filename, ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        if (!rec.empty) {
            rbTree->insert(rec.FIO,fileIndex);
        }
        cout<<rec;
        fileIndex++;
    }


    char FIO[100];
    rbTree->display();
    cout<<"\n\n\n\n\n";
    strcpy_s(FIO, "Surname57 Name58 Otchestvo87");

    // Time consumed
//    auto start = std::chrono::system_clock::now();
//    // 15: 1799968149 1200446723
//    // 100: 476514495
//    // 1000: 1739882252
//    // 2000: 40715941
//    // 5000: 938504129
//    // 10000: 1353653019
//    cout << binFile.findRecord(1353653019, binTree);
//
//    auto end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed = end - start;
//    std::cout << elapsed.count() << " s" << '\n';
//
//    binTree->display(0, binTree);
//
//    binTree = binTree->deleteItem(binTree, 1200446723);
//    cout << "----------------------------------" << endl;
//    binTree->display(0, binTree);
//
//
//    // ??? ??????
//    AVLTree* avltree = new AVLTree();
//    int fileIndex = 0;
//    ifstream fin(filename, ios::binary | ios::in);
//    record rec;
//    while (!fin.eof()) {
//        fin.read((char*)&rec, sizeof(record));
//        //cout << rec;
//        if (!rec.empty)
//        {
//            if (fileIndex == 0) {
//                avltree = avltree->addNode(rec.license, fileIndex);
//            }
//            else
//                avltree = avltree->addNode(rec.license, fileIndex, avltree);
//        }
//        fileIndex++;
//    }
//
//    auto start = std::chrono::system_clock::now();
//    // 15: 1799968149 1200446723
//    // 100: 476514495
//    // 1000: 1739882252
//    // 2000: 40715941
//    // 5000: 938504129
//    // 10000: 1353653019
//    cout << findRecord(1353653019, avltree);
//
//    // Time consumed
//    auto end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed = end - start;
//    std::cout << elapsed.count() << " s" << '\n';
//
//    avltree->display(0, avltree);
//    cout << "Total rotations: " << avltree->getRotations() << endl;
//    cout << "----------------------------------" << endl;
//
//    avltree = avltree->deleteNode(1200446723, avltree);
//    avltree->display(0, avltree);
//    cout << "Total rotations: " << avltree->getRotations() << endl;
//
//
//
//
//
//    // RAM used
//    // ??????? ??????????
//    // ????? windows.h ? psapi.h
//    PROCESS_MEMORY_COUNTERS_EX pmc;
//    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
//    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
//    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
//    std::cout << physMemUsedByMe << '\n';

    return 0;
}
