
#include <iostream>
#include "Client.h"
#include "FileAttente.h"
#include "GenerateClient.h"
#include <vector>

using namespace std;

void displayList(list<Client*> &Liste)
{
	cout << "{ ";
	for (const Client* client : Liste) {
		cout << client->getPrenom() << ", ";
	}
	cout << " }";
}

int main()
{
	locale::global(locale{ "" });

	cout << "Bonjour à tous !" << endl;

	Client personne1 = Client("BUET", "Quentin", 22, "quentinbuet4@gmail.com");
	Client personne2 = Client("VW", "Jean", 21, "jeanvw007@gmail.com");
	Client personne3 = Client("BOUILLON", "Dylan", 20, "d.bouillon@gmail.com");

	FileAttente File;
	File.addClient(&personne1);
	File.addClient(&personne2);
	File.addClient(&personne3);
	File.addClient(&personne1);

	list<Client*> ListeFileAttente = File.getAll();

	displayList(ListeFileAttente);

	File.removeClient(&personne1);

	ListeFileAttente = File.getAll();

	displayList(ListeFileAttente);

	for (int i = 0; i < 100; i++)
	{
		cout << GetRandomInt(0,5) << endl;
	}
	
	return 0;
}