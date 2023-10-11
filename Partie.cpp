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

void Partie::CreateListeMines(string Mine1, string Mine2, string Mine3, string Mine4)
{
    this->ListeMines[0] = new Mine(Mine1, 2, 2, 5);
    this->ListeMines[1] = new Mine(Mine2, 2, 2, 5);
    this->ListeMines[2] = new Mine(Mine3, 2, 2, 5);
    this->ListeMines[3] = new Mine(Mine4, 2, 2, 5);
}