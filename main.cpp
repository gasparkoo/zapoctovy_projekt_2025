#include <string>
#include "generovanie.h"
#include "levenshtein.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
using namespace std;

int main() {
    srand(time(NULL));

    CountingDistance distance("konfiguracia.txt");

    int dlzka_vyg_text;                                       //dlzka textu
    cout << "Napis dlzku vygenerovaneho textu: " ;
    cin >> dlzka_vyg_text;
    cin.ignore(1);
    auto generovanie = GeneratorTextu::zo_suboru("text.txt");
    string vygenerovany_text = generovanie.generuj(dlzka_vyg_text);
    cout << vygenerovany_text << endl;
    string napisany_text;
    cout << "Mozes pisat" << endl;
    auto start = chrono::system_clock::now();                   //zaciatok casovania
    getline(cin,napisany_text);
    auto end = chrono::system_clock::now();                     //koniec casovania
    auto elapsed = chrono::duration_cast<chrono::seconds>(end-start);
    cout << "cas: " << elapsed.count() << endl;
    cout << "chybovost: " << distance.chybovost(napisany_text,vygenerovany_text) << endl;
    int pocet_slov = dlzka_vyg_text/5;
    float WPM = (float) pocet_slov/elapsed.count()*60;
    cout << "WPM: " << WPM <<endl;

}