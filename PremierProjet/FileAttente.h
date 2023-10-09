#pragma once
#include "Client.h"
#include <list>

class FileAttente
{
public:
	void addClient(Client* ClientInput);
	void removeClient(Client* ClientInput);
	Client* getCurrent();
	list <Client*> getAll();

private:
	list <Client*> File;
};

