
#include <stdio.h>
#include <stdlib.h>

void LaunchMenu()
{
	// ****************************************************************************** //
	// Cette fonction permet de lancer le début de l'application en affichant le menu //
	// Elle permet de sélectionner un élément de menu et de rediriger le joueur vers  //
	// ce qu'il aura choisi.                                                          //
	// ****************************************************************************** //

	printf("Bienvenue dans MineItAll !\n\n");
	printf("1: Lancer le jeu\n");
	printf("2: Règles du jeu\n");
	printf("3: Quitter le jeu\n\n");

	int PlayerInput;

	while (1) // Boucle infinie tant que l'input du joueur n'est pas correct
	{
		printf("Afin de naviguer de le menu, Veuillez entrer un chiffre entre 1 et 3: ");

		if (scanf_s("%d", &PlayerInput) == 1) // Si l'input correspond bien à un integer
		{
			if (1 <= PlayerInput && PlayerInput <= 4) // Si l'input est bien compris entre 1 et 3
			{
				break; // Si les conditions sont remplies, on quitte la boucle infinie
			}
		}
		else
		{
			while (getchar() != '\n'); // Permet de nettoyer le tampon d'entrée et d'attendre l'input de l'utilisateur à la prochaine itération de la boucle
		}
	}

	switch (PlayerInput)
	{
		case 1:
			StartGame();
			break;
		case 2:
			GameRules();
			break;
		case 3:
			exit(0);
	}
}

struct Jeu
{
	unsigned int Tour[2];
	char* ListeJoueurs[4];
	unsigned int ListeScores[4];
};

void StartGame()
{
	// ****************************************** //
	// Cette fonction permet de lancer la partie. //
	// Elle permet de gérer tout le jeu de A à Z  //
	// ****************************************** //

	struct Jeu VariablesJeu = {
		{1, 10},
		{"Joueur 1", "Joueur 2", "Joueur 3", "Joueur 4"},
		{ 0, 0, 0, 0 }
	};

	for (VariablesJeu.Tour[0]; VariablesJeu.Tour[0] <= VariablesJeu.Tour[1]; VariablesJeu.Tour[1]++)
	{
		for (int NumeroJoueur = 0; NumeroJoueur < sizeof(VariablesJeu.ListeJoueurs); NumeroJoueur++)
		{
			PlayerTurn(NumeroJoueur, VariablesJeu);
		}
	}
}

void PlayerTurn(const int NumeroJoueur, struct Jeu VariablesJeu)
{
	printf("C'est à %s de jouer !", VariablesJeu.ListeJoueurs[NumeroJoueur]);
}

void GameRules()
{
	// *************************************************** //
	// Cette fonction permet d'afficher les règles du jeu. //
	// Elle renvoie directement après à LaunchMenu()       //
	// *************************************************** //

	printf("Explication des règles du jeu:\n\n");

	LaunchMenu();
}