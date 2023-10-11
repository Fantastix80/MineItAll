#include "Mine.h"

Mine::Mine(string Nom, int CapaciteMax, int DureeMinage, int Gain)
{
    this->Nom = Nom;
    this->CapaciteMax = CapaciteMax;
    this->DureeMinage = DureeMinage * 4;
    this->MinageEnCours = 0;
    this->Gain = DureeMinage * Gain;
}
