#include <string>
#include "generovanie.h"
#include "levenshtein.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
    srand(time(NULL));

    CountingDistance distance("konfiguracia.txt");

    std::string slovo1, slovo2;
    std::cin >> slovo1 >> slovo2;
    std::cout << "Vzdialenost: " << distance.chybovost(slovo1, slovo2) << std::endl;

    int dlzka_vyg_text = 200;                                       //dlzka textu
    auto generovanie = GeneratorTextu::zo_suboru("text.txt");
    std::cout << generovanie.generuj(dlzka_vyg_text);
    
}