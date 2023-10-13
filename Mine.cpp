#include "Mine.h"
#include "Player.h"
#include <QDebug>

Mine::Mine(int NumeroMine, string Nom, int CapaciteMax, int DureeMinage, int Gain)
{
    this->Numero = NumeroMine;
    this->Nom = Nom;
    this->CapaciteMax = CapaciteMax;
    this->DureeMinage = DureeMinage * 4;
    this->MinageEnCours = 0;
    this->Gain = DureeMinage * Gain;
    this->ListeMineursPresents = {};
}

/*Mine::~Mine()
{
    // Appeler la fonction pour libérer les joueurs et les mines
    qDebug() << "Debug Mine #1";
    ClearListeMineurs();
}

void Mine::ClearListeMineurs()
{
    qDebug() << "Debug Mine #2";
    // Libérer les joueurs
    for (int i = 0; i < (int)ListeMineursPresents.size(); ++i)
    {
        qDebug() << "Debug Mine #3-"<<i;
        ListeMineursPresents[i]->GetPlayerName();
        delete ListeMineursPresents[i];
    }
}*/
