#include "Player.h"
#include <string>

using namespace std;

Player::Player(string PlayerName)
{
    this->Name = PlayerName;
    this->Coins = 0;
    this->Miners = 0;
}

string Player::GetPlayerName()
{
    return this->Name;
}

int Player::GetPlayerCoins()
{
    return this->Coins;
}


int Player::GetPlayerMiners()
{
    return this->Miners;
}

