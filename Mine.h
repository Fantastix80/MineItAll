#ifndef MINE_H
#define MINE_H

#include "Player.h"
#include <string>

using namespace std;


class Mine
{
public:
    Mine(string Name, int CapaciteMax, int DureeMinage, int Gain);

    // Variables
    string Nom;
    int CapaciteMax;
    int DureeMinage;
    int Gain;
    Player* ListeMineursPresents[];
};

#endif // MINE_H
