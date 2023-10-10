
#include "GenerateClient.h"
#include <stdio.h>
#include <stdlib.h>


int GetRandomInt(int ValeurMin, int ValeurMax)
{
    int ValeurModulo = ValeurMax - ValeurMin;
    int RandomInt = rand() % ValeurModulo + 1;
    int ResultInt = RandomInt + ValeurMin;

    return ResultInt;
}
/*
char* GetRandomNom()
{
    char TableauNom[10][15] = {
        "BOUILLON",
        "VAN WITTENBERGE",
        "BUET",
        "GAGNARD",
        "KAPLOUN",
        "MARTINS",
        "SELIN",
        "ALI ABBAS",
        "HADI",
        "GUILLAUMIN"
    };

    return TableauNom[GetRandomInt(0, 9)];
}

char* GetRandomPrenom()
{
    char TableauPrenom[10][8] = {
        "Jean",
        "Dylan",
        "Jason",
        "Quentin",
        "Helder",
        "Claude",
        "Mehdi",
        "Jules",
        "Pieter",
        "Jacques"
    };

    return TableauPrenom[GetRandomInt(0, 9)];
}

struct GenerationClient
{
    int numero;
    char* prenom;
    char* nom;
    int age;
    char* email;
};

struct GenerationClient GetRandomClient(const int NombresClients)
{
    struct GenerationClient Client1 = { 1, "Jean", "VAN", 21, "jeanvw007@gmail.com" };

    printf("Client n°%d", Client1.numero);
}*/
