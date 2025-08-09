#pragma once
#include <tuple>
#include <string>

class Operacia{
    public:
    virtual std::tuple <int,int,int> vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne) = 0;
    int cena;
};

class Substitution :public Operacia{
    public:
    virtual std::tuple <int,int,int> vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne);
    Substitution(int cena) {
        this->cena = cena;
    }
};

class Insertion :public Operacia{
    public:
    virtual std::tuple <int,int,int> vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne);
    Insertion(int cena) {
        this->cena = cena;
    }
};

class Deletion :public Operacia{
    public:
    virtual std::tuple <int,int,int> vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne);
    Deletion(int cena) {
        this->cena = cena;
    }
};

class Transposition :public Operacia{
    public:
    virtual std::tuple <int,int,int> vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne);
    Transposition(int cena) {
        this->cena = cena;
    }
};
