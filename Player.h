#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
public:
    Player(std::string PlayerName);
    std::string GetPlayerName();
    int GetPlayerCoins();
    int GetPlayerMiners();

private:
    std::string Name;
    int Coins;
    int Miners;
};

#endif // PLAYER_H
