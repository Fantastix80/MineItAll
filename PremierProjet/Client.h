#pragma once
#include <iostream>
#include <string>

using namespace std;

class Client
{
public:
	Client(string const NomInput, string const PrenomInput, unsigned int const AgeInput, string const EmailInput);
	string getNom() const;
	string getPrenom() const;
	int getAge() const;
	string getEmail() const;

	void setNom(string const NomInput);
	void setPrenom(string const PrenomInput);
	void setAge(unsigned int const AgeInput);
	void setEmail(string const EmailInput);

private:
	string Nom, Prenom, Email;
	unsigned int Age;
};

