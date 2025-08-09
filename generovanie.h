#pragma once

#include<string>
#include<unordered_map>

class Mapa {
    std::unordered_map<char, int> mapa;
    int sucet;
    public:
    void pridaj_vyskyt(char c);
    char vygeneruj_nahodny();
};

class GeneratorTextu {
    std::unordered_map<std::string, Mapa> slovnik;
    int par;

    public:
    GeneratorTextu(int par, std::string& text);
    std::string generuj(int dlzka);
};