#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Partie.h"
#include <string>

#include <qDebug>

using namespace std;

extern "C"
{
int f()
{
    return 3;
}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << f();

    // On initialise la partie
    PartieEnCours = Partie();

    // On ajoute les joueurs à la partie (Ils seront créés par la classe Partie)
    PartieEnCours.CreateListeJoueurs("Joueur 1", "Joueur 2", "Joueur 3", "Joueur 4");

    // On vient compléter l'affichage avec les informations des joueurs
    InitialisePlayersDisplay();

    // On vient compléter l'affichage avec les informations des mines
    InitialiseMinesDisplay();

    // On ajoute les mines à la partie (Elles seront créées par la classe Partie)
    PartieEnCours.CreateListeMines("Mine #1", "Mine #2", "Mine #3", "Mine #4");

    // Connection des boutons pour entrer dans les mines
    connect(ui->Mine1Enter, &QPushButton::clicked, this, [this]{ EnterMine(1); });
    connect(ui->Mine2Enter, &QPushButton::clicked, this, [this]{ EnterMine(2); });
    connect(ui->Mine3Enter, &QPushButton::clicked, this, [this]{ EnterMine(3); });
    connect(ui->Mine4Enter, &QPushButton::clicked, this, [this]{ EnterMine(4); });

    // Par défaut on cache la progressBar indiquant à quelle point les mineurs en sont dans leurs minages
    ui->Player1MinerWorkingProgress->hide();
    ui->Player2MinerWorkingProgress->hide();
    ui->Player3MinerWorkingProgress->hide();
    ui->Player4MinerWorkingProgress->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnterMine(int MineAEntrer)
{
    qDebug() << "Le mineur du joueur " << PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerName() << " envoyé dans la mine " << MineAEntrer;

    // On vient incrémenter la variable qui garde en mémoire le tour du joueur qui doit jouer
    PartieEnCours.TourJoueur++;

    // Si on vient de passer le tour du 4ème joueur:
    if (PartieEnCours.TourJoueur == 4)
    {
        PartieEnCours.TourJoueur = 0; // On remet le tour au premier joueur
        PartieEnCours.TourActuel++; // Et on incrémente le nombre de tour joués
        DisplayCurrentRound(PartieEnCours.TourActuel);

        // Si on dépasse le nombre de tour maximum:
        if (PartieEnCours.TourActuel > PartieEnCours.TourTotal)
        {
            qDebug() << "Fin de la partie";
            //Faire un programme pour annoncer le gagnant et fermer l'application
        }
    }

    // On vient actualiser l'affichage du joueur qui doit jouer
    DisplayPlayersTurnName(PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerName());
}

void MainWindow::DisplayCurrentRound(int CurrentRound)
{
    ui->Round->setText("Tour " + QString::number(CurrentRound));
}

void MainWindow::SetCantPlayLabel(string Message)
{
    ui->CantPlayLabel->setText(QString::fromStdString(Message));
}

void MainWindow::DisplayPlayersTurnName(string PlayerName)
{
    ui->CurrentPlayersName->setText(QString::fromStdString(PlayerName));
}

void MainWindow::InitialisePlayersDisplay()
{
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[0]->GetPlayerName()));
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[1]->GetPlayerName()));
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[2]->GetPlayerName()));
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[3]->GetPlayerName()));
}

void MainWindow::InitialiseMinesDisplay()
{

}
