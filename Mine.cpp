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
