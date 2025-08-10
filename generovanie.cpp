#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "generovanie.h"
using namespace std;

void Mapa::pridaj_vyskyt(char c) {
    mapa[c] += 1;
    sucet += 1;
}

char Mapa::vygeneruj_nahodny() {
    int nahodne_cislo = rand()%sucet; 
    int suma = 0;
    for(auto prvok : mapa) {
        suma+=prvok.second;
        if(suma>nahodne_cislo){
            return prvok.first;
        }
    }
}

GeneratorTextu::GeneratorTextu(int par, string& text) : par(par) {
    for(int i=0;i<text.length()-par;i++){
        string ntica = text.substr(i,par);
        char pismenko = text[i+par];
        slovnik[ntica].pridaj_vyskyt(pismenko);
    }
}

string GeneratorTextu::generuj(int dlzka) {
    string gen_text= slovnik.begin()->first;
    string ktica = gen_text;
    for(int i=0;i<dlzka-par;i++){
        gen_text += slovnik[ktica].vygeneruj_nahodny();
        ktica = gen_text.substr(i+1,par);
            
    }
    return gen_text;
}

GeneratorTextu GeneratorTextu::zo_suboru(string nazov_suboru){
    ifstream fin(nazov_suboru);
    string word,text;
    while (fin >> word){
        text+=word+" ";
    }
    return GeneratorTextu(4,text);                  //parameter
}
