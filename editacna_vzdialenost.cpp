#include "editacna_vzdialenost.h"
using namespace std;

tuple<int,int,int> Transposition::vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne){
    if(napis<2){
        return {0,0,0};
    }
    int a = 0;
    if(spravne_slovo[spravne-1] == napis_slovo[napis-2]){
        a+=1;
    }
    if(spravne>1 && spravne_slovo[spravne-2] == napis_slovo[napis-1]){
        a+=1;
    }
    return {a,a,cena};
}

tuple<int,int,int> Substitution::vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne){
    if(napis == 0 || spravne == 0){
        return {0,0,0};
    }
    return {1,1,cena};
}

tuple<int,int,int> Deletion::vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne){
    if(napis == 0){
        return {0,0,0};
    }
    return {1,0,cena};
}

tuple<int,int,int> Insertion::vykonaj(const std::string& napis_slovo, const std::string& spravne_slovo, int napis, int spravne){
    if(spravne == 0){
        return {0,0,0};
    }
    return {0,1,cena};
}
