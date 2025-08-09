#pragma once
#include "editacna_vzdialenost.h"
#include <vector>

class CountingDistance{
    public:
    int chybovost(const std::string& napis_slovo ,const std::string& spravne_slovo);
    std::vector<Operacia*> operacie;
};