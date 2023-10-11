#ifndef MINE_H
#define MINE_H

#include <string>
#include <vector>

using namespace std;

class Player;

class Mine
{
public:
    Mine(string Name, int CapaciteMax, int DureeMinage, int Gain);

    // Variables
    string Nom;
    int CapaciteMax;
    int DureeMinage;
    int MinageEnCours;
    int Gain;
    //Player* ListeMineursPresents[];
    vector<Player*> ListeMineursPresents;
};

#endif // MINE_H
