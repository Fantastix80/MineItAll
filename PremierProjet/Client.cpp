#include "Client.h"

Client::Client(string const NomInput, string const PrenomInput, unsigned int const AgeInput, string const EmailInput)
{
    this->Nom = NomInput;
    this->Prenom = PrenomInput;
    this->Age = AgeInput;
    this->Email = EmailInput;
}

string Client::getNom() const
{
    return this->Nom;
}

string Client::getPrenom() const
{
    return this->Prenom;
}

int Client::getAge() const
{
    return this->Age;
}

string Client::getEmail() const
{
    return this->Email;
}

void Client::setNom(string const NomInput)
{
    this->Nom = NomInput;
}

void Client::setPrenom(string const PrenomInput)
{
    this->Prenom = PrenomInput;
}

void Client::setAge(unsigned int const AgeInput)
{
    this->Age = AgeInput;
}

void Client::setEmail(string const EmailInput)
{
    this->Email = EmailInput;
}
