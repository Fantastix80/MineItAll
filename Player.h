#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Mine;

class Player
{
public:
    Player(std::string PlayerName);
    std::string GetPlayerName();
    int GetPlayerCoins();
    int GetPlayerMiners();
    void SetPlayerCoins(int NewAmountOfCoins);
    void SetPlayerMiners(int NewAmountOfMiners);

private:
    std::string Name;
    int Coins;
    int Miners;
    Mine* WhereIsMiner;
};

#endif // PLAYER_H
