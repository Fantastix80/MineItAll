#include "Partie.h"


Partie::Partie()
{
    this->TourActuel = 1;
    this->TourTotal = 10;
    this->NombreJoueurs = 4;
    this->TourJoueur = 0;
}

void Partie::CreateListeJoueurs(string Joueur1, string Joueur2, string Joueur3, string Joueur4)
{
    this->ListeJoueurs[0] = new Player(Joueur1);
    this->ListeJoueurs[1] = new Player(Joueur2);
    this->ListeJoueurs[2] = new Player(Joueur3);
    this->ListeJoueurs[3] = new Player(Joueur4);
}

extern "C"
{
    int GetRandomInt(int MinInt, int MaxInt)
    {
        int TempInt = MaxInt - MinInt;
        int RandomInt = rand() % (TempInt + 1);
        int ResultInt = RandomInt + MinInt;

        return ResultInt;
    }
};

void Partie::CreateListeMines(string Mine1, string Mine2, string Mine3, string Mine4)
{
    this->ListeMines[0] = new Mine(Mine1, GetRandomInt(1,3), GetRandomInt(1,5), GetRandomInt(1,3));
    this->ListeMines[1] = new Mine(Mine2, GetRandomInt(1,3), GetRandomInt(1,5), GetRandomInt(1,3));
    this->ListeMines[2] = new Mine(Mine3, GetRandomInt(1,3), GetRandomInt(1,5), GetRandomInt(1,3));
    this->ListeMines[3] = new Mine(Mine4, GetRandomInt(1,3), GetRandomInt(1,5), GetRandomInt(1,3));
}
