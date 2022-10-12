#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Siaod2/Map.h"
using namespace std;
//Вариант 4
struct CarOwner{
    string carNumber;
    string carBrand;
    string name;
    string surname;
    int age;

    CarOwner(){}

    CarOwner(const string &carNumber,
             const string &carBrand,
             const string &name,
             const string &surname,
             const int &age) :
             carNumber(carNumber),
             carBrand(carBrand),
             name(name),
             surname(surname),
             age(age) {}
};

std::ostream& operator << (std::ostream &os, const CarOwner &p)
{
    return os <<p.carNumber<<setw(12)<<p.carBrand<<setw(12)<<p.name<<setw(12)<<p.surname<<setw(5)<<p.age;
}

std::istream& operator >> (std::istream& in, CarOwner& p)
{
    in >>p.carNumber>>p.carBrand>>p.name>>p.surname>>p.age;;
    return in;
}

string randCarNumber(){
    string str(6,'1');
    str[0] = 'a'+rand()%25;
    str[1] = '0'+rand()%9;
    str[2] = '0'+rand()%9;
    str[3] = '0'+rand()%9;
    str[4] = 'a'+rand()%25;
    str[5] = 'a'+rand()%25;

    return str;
}
string* randName = new string[10]{
        "Abraham",
        "Adam",
        "Adrian",
        "Albert",
        "Arnold",
        "Ashley",
        "Austen",
        "Calvin",
        "Carl",
        "Chad"
};
string* randSurName = new string[10]{
        "Abramson",
        "Adderiy",
        "Albertson",
        "Allford",
        "Alsopp",
        "Arnold",
        "Backer",
        "Benson",
        "Blomfield",
        "Bosworth"
};
string* brand = new string[10]{
        "AUDI",
        "ACURA",
        "CHERY",
        "FAW",
        "KIA",
        "JAGUAR",
        "MAZDA",
        "MERCEDES",
        "MCLAREN",
        "TOYOTA"

};
void fileGenerate(int n){
    ofstream fout("F:\\Siaod\\Siaod2\\file.txt");
    for (int i=0; i<n; i++){
        CarOwner carOwner(
                randCarNumber(),
                brand[rand()%10],
                randName[rand()%10],
                randSurName[rand()%10],
                rand()%50+20
                );
        fout<<carOwner;
    }

}

void file_read(string file, Map  &map){
    CarOwner carOwner;
    ifstream fin(file);
    int i=0;
    while(!fin.eof()){
        fin>>carOwner;
        map.insertItem(carOwner.carNumber,i+1);
        i++;
    }
}

void file_del_data(string file,Map& map, string key){
    int fileIndex = map.deleteItem(key);

    list<string> list1;
    string line;
    ifstream fin(file);
    int i = 1;
    while (getline(fin, line)) {
        if (i != fileIndex) {
            list1.push_back(line);
        }
        i++;
    }
    fin.close();
    ofstream fout(file);
    for (auto line: list1){
        fout<<line<<endl;
    }
    fout.close();
}

void file_add_data(string file,Map& map){
    CarOwner carOwner(
            randCarNumber(),
            brand[rand()%10],
            randName[rand()%10],
            randSurName[rand()%10],
            rand()%50+20
    );
    ofstream fout(file, ios::app);
    fout<<endl<<carOwner;
    map.insertItem(carOwner.carNumber, map.getSize()+1);
}

int main() {
    srand(time(NULL));
    string file = "F:\\Siaod\\Siaod2\\file.txt";
    Map map(40);
    file_read(file, map);
    for (int i = 0; i < 10; ++i) {
        file_add_data(file,map);
    }
    map.displayHash();
    return 0;
}
