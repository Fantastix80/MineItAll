#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Partie.h"
#include <string>
#include <synchapi.h>

#include <qDebug>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), Timer (new QTimer)
{
    ui->setupUi(this);

    Timer->start(1000);
    connect(Timer, &QTimer::timeout, this, &MainWindow::ActionTimer);

    // On initialise la partie
    PartieEnCours = Partie();

    // On ajoute les joueurs à la partie (Ils seront créés par la classe Partie)
    PartieEnCours.CreateListeJoueurs("Joueur 1", "Joueur 2", "Joueur 3", "Joueur 4");

    // On vient compléter l'affichage avec les informations des joueurs
    InitialisePlayersDisplay();

    // On ajoute les mines à la partie (Elles seront créées par la classe Partie)
    PartieEnCours.CreateListeMines("Mine #1", "Mine #2", "Mine #3", "Mine #4");

    // On vient compléter l'affichage avec les informations des mines
    InitialiseMinesDisplay();

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

void MainWindow::ActionTimer()
{
    ui->TimerTimeLeft->setValue(ui->TimerTimeLeft->value() + 1);
}

int MainWindow::EnterMine(int MineAEntrer)
{
    // On vient désactiver tous les boutons pour éviter les spams et donc les bugs
    DesactivateAllButton();

    if ((int)PartieEnCours.ListeMines[MineAEntrer-1]->ListeMineursPresents.size() < PartieEnCours.ListeMines[MineAEntrer-1]->CapaciteMax)
    {
        if (PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerMiners() > 0)
        {
            PartieEnCours.ListeMines[MineAEntrer-1]->ListeMineursPresents.push_back(PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]);
            PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->SetPlayerMiners(PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerMiners()-1);

            // On vient afficher la progress bar du mineur
            int Numero = PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerNumber();
            switch (Numero)
            {
            case 1:
                ShowProgressBar(ui->Player1MinerWorkingProgress);
                break;
            case 2:
                ShowProgressBar(ui->Player2MinerWorkingProgress);
                break;
            case 3:
                ShowProgressBar(ui->Player3MinerWorkingProgress);
                break;
            case 4:
                ShowProgressBar(ui->Player4MinerWorkingProgress);
                break;
            }

            //MESSAGE DEBUG
            qDebug() << "joueur:" << PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerName() << ", mine:" << PartieEnCours.ListeMines[MineAEntrer-1]->Nom << ", Mineur présent" << PartieEnCours.ListeMines[MineAEntrer-1]->ListeMineursPresents[0]->GetPlayerName() << ", Minage en cours:" << PartieEnCours.ListeMines[MineAEntrer-1]->MinageEnCours << ", Duree Minage:" << PartieEnCours.ListeMines[MineAEntrer-1]->DureeMinage;
        }
        else
        {
            // On vient réactiver tous les boutons
            ReactivateAllButton();

            return 0;
        }
    }
    else
    {
        vector<Player*> joueurs =  PartieEnCours.ListeMines[0]->ListeMineursPresents;
        for (Player* j : joueurs)
        {
            qDebug() << j;
        }

        SetCantPlayLabel("Vous ne pouvez pas rentrer dans cette mine car elle est pleine.");

        // On vient réactiver tous les boutons
        ReactivateAllButton();

        return 0;
    }

    // On vient passer au tour suivant
    NextTurn();

    return 0;
}

void MainWindow::NextTurn()
{
    // On vient réactiver tous les boutons
    ReactivateAllButton();

    // On vient clear le label contenant les messages d'erreurs
    ClearCantPlayLabel();

    // Avant de passer au tour suivant, on vient faire travailler les mineurs
    MakeMinersWork();

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
            qDebug() << PartieEnCours.ListeJoueurs[0]->GetPlayerName() << PartieEnCours.ListeJoueurs[0]->GetPlayerCoins();
            qDebug() << PartieEnCours.ListeJoueurs[1]->GetPlayerName() << PartieEnCours.ListeJoueurs[1]->GetPlayerCoins();
            qDebug() << PartieEnCours.ListeJoueurs[2]->GetPlayerName() << PartieEnCours.ListeJoueurs[2]->GetPlayerCoins();
            qDebug() << PartieEnCours.ListeJoueurs[3]->GetPlayerName() << PartieEnCours.ListeJoueurs[3]->GetPlayerCoins();
            //Faire un programme pour annoncer le gagnant et fermer l'application
        }
    }

    // On vient regarder si le joueur suivant n'a pas de mineur disponible
    if (PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerMiners() == 0)
    {
        // On vient désactiver tous les boutons
        DesactivateAllButton();

        // On vient afficher le message d'erreur
        SetCantPlayLabel("Vous n'avez pas de mineurs de disponible vous sautez donc votre tour.");
        QTimer::singleShot(2000, this, &MainWindow::NextTurn);
    }

    // On vient actualiser l'affichage des données des joueurs et des mines
    DisplayPlayersTurnName(PartieEnCours.ListeJoueurs[PartieEnCours.TourJoueur]->GetPlayerName());
    InitialisePlayersDisplay();
    InitialiseMinesDisplay();
}

void MainWindow::MakeMinersWork()
{
    for (int NumeroMine = 0; NumeroMine < 4; NumeroMine++)
    {
        // Je viens incrémenter le minage en cours seulement s'il y a au moins 1 mineur présent dans la mine
        if (PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents.size() > 0)
        {
            PartieEnCours.ListeMines[NumeroMine]->MinageEnCours++;

            // On vient actualiser l'affichage de la progress bar des mineurs qui minent
            int Numero = PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerNumber();
            switch (Numero)
            {
                case 1:
                    UpdateProgressBar(ui->Player1MinerWorkingProgress, NumeroMine);
                    break;
                case 2:
                    UpdateProgressBar(ui->Player2MinerWorkingProgress, NumeroMine);
                    break;
                case 3:
                    UpdateProgressBar(ui->Player3MinerWorkingProgress, NumeroMine);
                    break;
                case 4:
                    UpdateProgressBar(ui->Player4MinerWorkingProgress, NumeroMine);
                    break;
            }
        }

        // On vient vérifier si le minage en cours est égale à la durée de minage
        if (PartieEnCours.ListeMines[NumeroMine]->MinageEnCours == PartieEnCours.ListeMines[NumeroMine]->DureeMinage)
        {
            // On remet le mineur dans le joueur ainsi que sa récompense
            PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->SetPlayerMiners(PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerMiners()+1);
            PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->SetPlayerCoins(PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerCoins() + PartieEnCours.ListeMines[NumeroMine]->Gain);

            // On vient ensuite réinitialiser la progress bar du mineur et la cacher
            int Numero = PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerNumber();
            switch (Numero)
            {
            case 1:
                    ClearAndHideProgressBar(ui->Player1MinerWorkingProgress);
                    break;
            case 2:
                    ClearAndHideProgressBar(ui->Player2MinerWorkingProgress);
                    break;
            case 3:
                    ClearAndHideProgressBar(ui->Player3MinerWorkingProgress);
                    break;
            case 4:
                    ClearAndHideProgressBar(ui->Player4MinerWorkingProgress);
                    break;
            }

            // On enlève le mineur de la liste des mineurs présents dans la mine
            PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents.erase(PartieEnCours.ListeMines[NumeroMine]->ListeMineursPresents.begin());

            // Puis on vient réinitialiser la variable MinageEnCours de la mine
            PartieEnCours.ListeMines[NumeroMine]->MinageEnCours = 0;
        }
    }
}

void MainWindow::DisplayCurrentRound(int CurrentRound)
{
    ui->Round->setText("Tour " + QString::number(CurrentRound));
}

void MainWindow::SetCantPlayLabel(string Message)
{
    ui->CantPlayLabel->setText(QString::fromStdString(Message));
}

void MainWindow::ClearCantPlayLabel()
{
    ui->CantPlayLabel->setText(QString::fromStdString(""));
}

void MainWindow::DisplayPlayersTurnName(string PlayerName)
{
    ui->CurrentPlayersName->setText(QString::fromStdString(PlayerName));
}

void MainWindow::InitialisePlayersDisplay()
{
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[0]->GetPlayerName()));
    ui->Player2Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[1]->GetPlayerName()));
    ui->Player3Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[2]->GetPlayerName()));
    ui->Player4Label->setText(QString::fromStdString(PartieEnCours.ListeJoueurs[3]->GetPlayerName()));

    ui->Player1Score->setText(QString::number(PartieEnCours.ListeJoueurs[0]->GetPlayerCoins()));
    ui->Player2Score->setText(QString::number(PartieEnCours.ListeJoueurs[1]->GetPlayerCoins()));
    ui->Player3Score->setText(QString::number(PartieEnCours.ListeJoueurs[2]->GetPlayerCoins()));
    ui->Player4Score->setText(QString::number(PartieEnCours.ListeJoueurs[3]->GetPlayerCoins()));

    ui->Player1MinerAvailable->setText(QString::number(PartieEnCours.ListeJoueurs[0]->GetPlayerMiners()));
    ui->Player2MinerAvailable->setText(QString::number(PartieEnCours.ListeJoueurs[1]->GetPlayerMiners()));
    ui->Player3MinerAvailable->setText(QString::number(PartieEnCours.ListeJoueurs[2]->GetPlayerMiners()));
    ui->Player4MinerAvailable->setText(QString::number(PartieEnCours.ListeJoueurs[3]->GetPlayerMiners()));
}

void MainWindow::InitialiseMinesDisplay()
{
    ui->Mine1Title->setText(QString::fromStdString(PartieEnCours.ListeMines[0]->Nom));
    ui->Mine2Title->setText(QString::fromStdString(PartieEnCours.ListeMines[1]->Nom));
    ui->Mine3Title->setText(QString::fromStdString(PartieEnCours.ListeMines[2]->Nom));
    ui->Mine4Title->setText(QString::fromStdString(PartieEnCours.ListeMines[3]->Nom));

    ui->Mine1CurrentMiners->setText(QString::number(PartieEnCours.ListeMines[0]->ListeMineursPresents.size()));
    ui->Mine2CurrentMiners->setText(QString::number(PartieEnCours.ListeMines[1]->ListeMineursPresents.size()));
    ui->Mine3CurrentMiners->setText(QString::number(PartieEnCours.ListeMines[2]->ListeMineursPresents.size()));
    ui->Mine4CurrentMiners->setText(QString::number(PartieEnCours.ListeMines[3]->ListeMineursPresents.size()));

    ui->Mine1TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours.ListeMines[0]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine2TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours.ListeMines[1]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine3TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours.ListeMines[2]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine4TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours.ListeMines[3]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
}

void MainWindow::DesactivateAllButton()
{
    ui->Mine1Enter->setDisabled(true);
    ui->Mine2Enter->setDisabled(true);
    ui->Mine3Enter->setDisabled(true);
    ui->Mine4Enter->setDisabled(true);
}

void MainWindow::ReactivateAllButton()
{
    ui->Mine1Enter->setEnabled(true);
    ui->Mine2Enter->setEnabled(true);
    ui->Mine3Enter->setEnabled(true);
    ui->Mine4Enter->setEnabled(true);
}

void MainWindow::ShowProgressBar(QProgressBar* ProgressBar)
{
    ProgressBar->setHidden(false);
}

void MainWindow::UpdateProgressBar(QProgressBar* ProgressBar, int NumeroMine)
{
    if (ProgressBar->maximum() != PartieEnCours.ListeMines[NumeroMine]->DureeMinage)
    {
        // On vient initialiser sa valeur max
        ProgressBar->setMaximum(PartieEnCours.ListeMines[NumeroMine]->DureeMinage);
    }

    // On incrémente sa valeur de 1
    ProgressBar->setValue(ProgressBar->value() + 1);
}

void MainWindow::ClearAndHideProgressBar(QProgressBar* ProgressBar)
{
    ProgressBar->setHidden(true);
    ProgressBar->setValue(0);
}
