#ifndef MINE_H
#define MINE_H

#include <string>
#include <vector>

using namespace std;

class Player;

class Mine
{
public:
    // Constructeur
    Mine(int NumeroMine, string Name, int CapaciteMax, int DureeMinage, int Gain);

    // Variables
    int Numero;
    string Nom;
    int CapaciteMax;
    int DureeMinage;
    int MinageEnCours;
    int Gain;
    vector<Player*> ListeMineursPresents;
};

#endif // MINE_H
