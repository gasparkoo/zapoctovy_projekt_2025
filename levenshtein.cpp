#include <iostream>
#include <vector>
#include <fstream>
#include "levenshtein.h"
using namespace std;

const int NEKONECNO = 1<<30;

int CountingDistance::chybovost(const std::string& napis_slovo ,const std::string& spravne_slovo){
    int dlzka_napis = napis_slovo.size();
    int dlzka_spravne = spravne_slovo.size();
    int matica[dlzka_napis+1][dlzka_napis+1];

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
    /*
    for (int i = 0;i < dlzka_napis+1;i++) {
        for (int j = 0;j < dlzka_spravne;j++) {
            std::cerr << matica[i][j]<< " ";
        }
        std::cerr << std::endl;
    }
        */

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

// int main(){


//     string word_1, word_2;
//     int dlzka_1,dlzka_2;
//     int stlpec,riadok,rozdiel;

//     cout << "Zadaj slova";
//     cin >> word_1;
//     cout << "Zadaj druhe";
//     cin >> word_2;
//     // cout << word_1 << " "<< word_2 << endl;
//     stlpec = dlzka_1 = word_1.length();
//     riadok = dlzka_2 = word_2.length();
//     int matica[riadok+1][stlpec+1];
//     for(int i=0;i<riadok+1;i++){
//         matica[i][0]=i;
//     }
//     for(int i=0;i<stlpec+1;i++){
//         matica[0][i]=i;
//     }
//     for (int i=1;i<riadok+1;i++){
//         for(int j=1;j<stlpec+1;j++){
//             if(word_1[j-1] == word_2[i-1]){
//                 matica[i][j] = min(matica[i-1][j-1],min(matica[i-1][j]+1,matica[i][j-1]+1));
//             }
//             else{
//             matica[i][j] = min(matica[i-1][j-1]+2,min(matica[i-1][j]+1,matica[i][j-1]+1)); //tu sa meni cena vykonanych akcii
//             }
//         }
//     }
//     for (int i=0; i<riadok+1;i++) {
//         for (int j=0;j<stlpec+1;j++) {
//             cout << matica[i][j] << " ";
//         }
//         cout << endl;
//     }
//     rozdiel = matica[riadok][stlpec];
// }