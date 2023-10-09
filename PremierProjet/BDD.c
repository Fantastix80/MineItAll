#include <mysql/mysql.h>
#include <stdio.h>

void ConnectBDD()
{
    // Initialiser la structure de connexion
    MYSQL* conn = mysql_init(NULL);

    // V�rifier si l'initialisation a r�ussi
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() a �chou�\n");
        return 1;
    }

    // �tablir la connexion � la base de donn�es
    if (mysql_real_connect(conn, "localhost", "root", "", "c_cpp_cinema", 0, NULL, 0) == NULL) {
        fprintf(stderr, "La connexion � la base de donn�es a �chou� : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // La connexion � la base de donn�es a r�ussi
    printf("Connect� � la base de donn�es MySQL en local\n");

    // Effectuez ici vos op�rations sur la base de donn�es

    // Fermer la connexion � la base de donn�es
    mysql_close(conn);
}