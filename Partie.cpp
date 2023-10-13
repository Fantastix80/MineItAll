#include "Partie.h"


Partie::Partie()
{
    this->TourActuel = 1;
    this->TourTotal = 10;
    this->NombreJoueurs = 4;
    this->TourJoueur = 0;
}

void Partie::CreateListeJoueurs(int NombreDeJoueurs, string PlayerNames[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (PlayerNames[i] == "")
        {
            PlayerNames[i] = "Joueur " + to_string(i+1);
        }
    }

    for (int i = 0; i < NombreDeJoueurs; i++)
    {
        this->ListeJoueurs[i] = new Player(i+1, PlayerNames[i], false);
    }

    int TempInt = 1;
    for (int i = NombreDeJoueurs; i < 4; i++)
    {
        this->ListeJoueurs[i] = new Player(i+1, "Bot " + to_string(TempInt), true);
        TempInt++;
    }
}

extern "C"
{
    int GetRandomIntC(int MinInt, int MaxInt)
    {
        int TempInt = MaxInt - MinInt;
        int RandomInt = rand() % (TempInt + 1);
        int ResultInt = RandomInt + MinInt;

        return ResultInt;
    }
};

int Partie::GetRandomInt(int MinInt, int MaxInt)
{
    return GetRandomIntC(MinInt, MaxInt);
}

void Partie::CreateListeMines(string Mine1, string Mine2, string Mine3, string Mine4)
{
    this->ListeMines[0] = new Mine(1, Mine1, GetRandomIntC(1,3), GetRandomIntC(1,5), GetRandomIntC(1,3));
    this->ListeMines[1] = new Mine(2, Mine2, GetRandomIntC(1,3), GetRandomIntC(1,5), GetRandomIntC(1,3));
    this->ListeMines[2] = new Mine(3, Mine3, GetRandomIntC(1,3), GetRandomIntC(1,5), GetRandomIntC(1,3));
    this->ListeMines[3] = new Mine(4, Mine4, GetRandomIntC(1,3), GetRandomIntC(1,5), GetRandomIntC(1,3));
}

Partie::~Partie()
{
    // Appeler la fonction pour libérer les joueurs et les mines
    ClearPlayersAndMines();
}

void Partie::ClearPlayersAndMines()
{
    // Libérer les joueurs
    for (int i = 0; i < 4; ++i)
    {
        delete ListeJoueurs[i];
    }

    // Libérer les mines
    for (int i = 0; i < 4; ++i)
    {
        delete ListeMines[i];
    }

}
