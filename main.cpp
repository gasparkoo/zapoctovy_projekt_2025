#include <string>
#include "generovanie.h"
#include "levenshtein.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
    srand(time(NULL));

    std::ifstream fin("text.txt");
    std::string text;
    std::string word;

    CountingDistance distance("konfiguracia.txt");

    std::string slovo1, slovo2;
    std::cin >> slovo1 >> slovo2;
    std::cout << "Vzdialenost: " << distance.chybovost(slovo1, slovo2) << std::endl;

    while (fin >> word){
        text+=word+" ";
    }
    int parameter = 4;
    int dlzka_vyg_text = 200;
    auto generovanie = GeneratorTextu(parameter,text);
    std::cout << generovanie.generuj(dlzka_vyg_text);
}