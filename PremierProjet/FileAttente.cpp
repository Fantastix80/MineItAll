#include <algorithm>
#include "FileAttente.h"


void FileAttente::addClient(Client* ClientInput)
{
	if (find(File.begin(), File.end(), ClientInput) != File.end())
	{
		printf("Cette personne est déjà dans la liste d'attente.");
	}
	else
	{
		File.push_back(ClientInput);
	}
}

void FileAttente::removeClient(Client* ClientInput)
{
	File.remove(ClientInput);
}

Client* FileAttente::getCurrent()
{
	return File.front();
}

list<Client*> FileAttente::getAll()
{
	return File;
}
