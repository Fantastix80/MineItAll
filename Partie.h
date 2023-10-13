#ifndef PARTIE_H
#define PARTIE_H

#include "Player.h"
#include "Mine.h"
#include <string>

using namespace std;


class Partie
{
public:
    // Constructeur
    Partie();

    // Destructeur
    ~Partie();

    // Fonctions
    void CreateListeJoueurs(int NombreDeJoueurs, string PlayerNames[4]);
    int GetRandomInt(int MinInt, int MaxInt);
    void CreateListeMines(string Mine1, string Mine2, string Mine3, string Mine4);
    void ClearPlayersAndMines();

    // Variables
    int TourActuel;
    int TourTotal;
    int NombreJoueurs;
    int TourJoueur;
    Player* ListeJoueurs[4];
    Mine* ListeMines[4];
};

#endif // PARTIE_H
