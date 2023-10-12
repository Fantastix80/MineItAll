#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Mine;

class Player
{
public:
    // Constructeurs
    Player(int PlayerNumber, std::string PlayerName);

    // Fonctions
    int GetPlayerNumber();
    std::string GetPlayerName();
    int GetPlayerCoins();
    int GetPlayerMiners();
    void SetPlayerCoins(int NewAmountOfCoins);
    void SetPlayerMiners(int NewAmountOfMiners);

private:
    int Number;
    std::string Name;
    int Coins;
    int Miners;
};

#endif // PLAYER_H
