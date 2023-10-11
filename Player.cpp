#include "Player.h"
#include <string>

using namespace std;

Player::Player(string PlayerName)
{
    this->Name = PlayerName;
    this->Coins = 0;
    this->Miners = 1;
}

string Player::GetPlayerName()
{
    return this->Name;
}

int Player::GetPlayerCoins()
{
    return this->Coins;
}

void Player::SetPlayerCoins(int NewAmountOfCoins)
{
    this->Coins = NewAmountOfCoins;
}


int Player::GetPlayerMiners()
{
    return this->Miners;
}

void Player::SetPlayerMiners(int NewAmountOfMiners)
{
    this->Miners = NewAmountOfMiners;
}

