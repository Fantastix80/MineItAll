#include <mysql/mysql.h>
#include <stdio.h>

void ConnectBDD()
{
    // Initialiser la structure de connexion
    MYSQL* conn = mysql_init(NULL);

    // Vérifier si l'initialisation a réussi
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() a échoué\n");
        return 1;
    }

    // Établir la connexion à la base de données
    if (mysql_real_connect(conn, "localhost", "root", "", "c_cpp_cinema", 0, NULL, 0) == NULL) {
        fprintf(stderr, "La connexion à la base de données a échoué : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // La connexion à la base de données a réussi
    printf("Connecté à la base de données MySQL en local\n");

    // Effectuez ici vos opérations sur la base de données

    // Fermer la connexion à la base de données
    mysql_close(conn);
}