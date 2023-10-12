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
    Mine(string Name, int CapaciteMax, int DureeMinage, int Gain);

    // Destructeur
    //~Mine();

    // Fonctions
    //void ClearListeMineurs();

    // Variables
    string Nom;
    int CapaciteMax;
    int DureeMinage;
    int MinageEnCours;
    int Gain;
    vector<Player*> ListeMineursPresents;
};

#endif // MINE_H
