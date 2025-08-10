#include <iostream>
#include <vector>
#include <fstream>
#include "levenshtein.h"
using namespace std;

const int NEKONECNO = 1<<30;

int CountingDistance::chybovost(const std::string& napis_slovo ,const std::string& spravne_slovo){
    int dlzka_napis = napis_slovo.size();
    int dlzka_spravne = spravne_slovo.size();
    int matica[dlzka_napis+1][dlzka_spravne+1];

    for (int i = 0;i < dlzka_napis+1;i++) {
        for (int j = 0;j < dlzka_spravne+1;j++) {
            matica[i][j] = NEKONECNO;
        }
    }

    matica[0][0] = 0;

    for (int i=0;i<dlzka_napis+1;i++){
        for(int j=0;j<dlzka_spravne+1;j++){
            if (i == 0 && j == 0) continue;
            int hodnota = NEKONECNO;
            if(napis_slovo[j-1] == spravne_slovo[i-1]){
                hodnota = min(hodnota, matica[i-1][j-1]);
            }
            for (auto operacia : operacie) {
                auto [napis, spravne, cena] = operacia->vykonaj(napis_slovo, spravne_slovo, i, j);
                hodnota = min(hodnota, matica[i-napis][j-spravne] + cena);
            }
            matica[i][j] = hodnota;
        }
    }

    return matica[dlzka_napis][dlzka_spravne];
}

CountingDistance::CountingDistance(string subor){
    ifstream fil(subor);
    std::string nova_operacia;
    int nova_cena;
    while (fil >> nova_operacia >> nova_cena){
        if(nova_operacia == "mazanie"){
            operacie.push_back(new Deletion(nova_cena));
        }
        if(nova_operacia == "pridavanie"){
            operacie.push_back(new Insertion(nova_cena));
        }
        if(nova_operacia == "transpozicia"){
            operacie.push_back(new Transposition(nova_cena));
        }
        if(nova_operacia == "substitucia"){
            operacie.push_back(new Substitution(nova_cena));
        }
    }

}
