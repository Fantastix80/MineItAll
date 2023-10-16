#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "minijeu.h"
#include "Partie.h"
#include <string>

#include <qDebug>
#include <QTimer>
#include <QMessageBox>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), PartieEnCours(nullptr)
{
    ui->setupUi(this);

    /*
    Listes des pages et de leur index:

    0: Menu
    1: Jeu Mine
    2: Règles du jeu
    3: Options du jeu
    4: ScoreBoard
    5: Mini Jeu
    */

    // On vient connecter les boutons du menu
    connect(ui->StartGameBtn, &QPushButton::clicked, this, &MainWindow::StartGame);
    connect(ui->GameRulesBtn, &QPushButton::clicked, this, [this]{ SwitchPages(2); });
    connect(ui->OptionsBtn, &QPushButton::clicked, this, [this]{ SwitchPages(3); });
    connect(ui->QuitGameBtn, &QPushButton::clicked, this, &MainWindow::QuitGame);

    // Menu Options

    // On connecte les boutons
    connect(ui->ReturnFromOptionsBtn, &QPushButton::clicked, this, [this]{ SwitchPages(0); });

    // On écoute un changement de la combo box qui contiendra le nombre de joueurs
    connect(ui->NumberOfPlayersValue, SIGNAL(currentTextChanged(QString)), this, SLOT(Options(QString)));

    // On vient cacher les noms des joueurs en trop pour matcher avec le nombre de joueur par défaut (1)
    ui->PlayerName2Container_2->hide();
    ui->PlayerName3Container_2->hide();
    ui->PlayerName4Container_2->hide();

    // Menu Règles

    // On vient connecter le bouton de retour
    connect(ui->ReturnFromReglesBtn, &QPushButton::clicked, this, [this]{ SwitchPages(0); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SwitchPages(int Index)
{
    ui->stackedWidget->setCurrentIndex(Index);
}

void MainWindow::Options(QString NumberOfPlayers)
{
    QList<QWidget*> widgetList = ui->PlayerNameContainer->findChildren<QWidget*>();

    // On vient boucler à travers la liste des widgets PlayerNameXContainer pour afficher ceux nécessaires
    for (int i = 0; i < NumberOfPlayers.toInt(); i++)
    {
        widgetList[i*3]->show();
    }

    // On vient boucler à travers la liste des widgets PlayerNameXContainer pour cacher ceux nécessaires
    for (int i = NumberOfPlayers.toInt(); i < 4; i++)
    {
        widgetList[i*3]->hide();
    }
}

void MainWindow::QuitGame()
{
    exit(0);
}

void MainWindow::StartGame()
{
    // On initialise la partie
    PartieEnCours = new Partie();

    // On ajoute les joueurs à la partie (Ils seront créés par la classe Partie)
    GetAndCreatePlayersInfo();

    // On vient compléter l'affichage avec les informations des joueurs
    InitialisePlayersDisplay();

    // On ajoute les mines à la partie (Elles seront créées par la classe Partie)
    PartieEnCours->CreateListeMines("Mine #1", "Mine #2", "Mine #3", "Mine #4");

    // On vient compléter l'affichage avec les informations des mines
    InitialiseMinesDisplay();

    // On vient afficher le round dans lequel on est et le nom du joueur dont s'est le tour
    DisplayCurrentRound(PartieEnCours->TourActuel);
    DisplayPlayersTurnName(PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerName());

    // On vient nettoyer le Label contenant le message d'erreur
    ClearCantPlayLabel();

    // On vient activer tous les boutons au cas ou ils seraient désactivé
    ReactivateAllButton();

    // Connection des boutons pour entrer dans les mines et pour quitter la partie
    connect(ui->Mine1Enter, &QPushButton::clicked, this, [this]{ EnterMine(1); });
    connect(ui->Mine2Enter, &QPushButton::clicked, this, [this]{ EnterMine(2); });
    connect(ui->Mine3Enter, &QPushButton::clicked, this, [this]{ EnterMine(3); });
    connect(ui->Mine4Enter, &QPushButton::clicked, this, [this]{ EnterMine(4); });
    connect(ui->LeaveGameBtn, &QPushButton::clicked, this, [this]{ ClearGame(true, 0); });

    // Par défaut on cache la progressBar indiquant à quelle point les mineurs en sont dans leurs minages
    ClearAndHideProgressBar(ui->Player1MinerWorkingProgress);
    ClearAndHideProgressBar(ui->Player2MinerWorkingProgress);
    ClearAndHideProgressBar(ui->Player3MinerWorkingProgress);
    ClearAndHideProgressBar(ui->Player4MinerWorkingProgress);

    // On vient afficher la page contenant le jeu
    SwitchPages(1);
}

int MainWindow::EnterMine(int MineAEntrer)
{
    // On vient désactiver tous les boutons pour éviter les spams et donc les bugs
    DesactivateAllButton();

    // Si la mine n'est pas pleine
    if ((int)PartieEnCours->ListeMines[MineAEntrer-1]->ListeMineursPresents.size() < PartieEnCours->ListeMines[MineAEntrer-1]->CapaciteMax)
    {
        // Si le joueur possède un mineur de disponible
        if (PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerMiners() > 0)
        {
            // On envoie le mineur dans la mine
            PartieEnCours->ListeMines[MineAEntrer-1]->ListeMineursPresents.push_back(PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]);
            PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->SetPlayerMiners(PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerMiners()-1);

            // On vient afficher la progress bar du mineur
            int Numero = PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerNumber();
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
        SetCantPlayLabel("Vous ne pouvez pas rentrer dans cette mine car elle est pleine.");

        // On vient réactiver tous les boutons
        ReactivateAllButton();

        return 0;
    }

    // On vient passer au tour suivant
    NextTurn();

    return 0;
}

int MainWindow::NextTurn()
{
    // On vient clear le label contenant les messages d'erreurs
    ClearCantPlayLabel();

    // Avant de passer au tour suivant, on vient faire travailler les mineurs
    MakeMinersWork();

    // On vient incrémenter la variable qui garde en mémoire le tour du joueur qui doit jouer
    PartieEnCours->TourJoueur++;

    // Si on vient de passer le tour du 4ème joueur:
    if (PartieEnCours->TourJoueur == 4)
    {
        PartieEnCours->TourJoueur = 0; // On remet le tour au premier joueur
        PartieEnCours->TourActuel++; // Et on incrémente le nombre de tour joués
        DisplayCurrentRound(PartieEnCours->TourActuel);

        // Si on dépasse le nombre de tour maximum:
        if (PartieEnCours->TourActuel > PartieEnCours->TourTotal)
        {
            DisplayScoreBoard();
            SwitchPages(4);
            ClearGame(false, 0);

            return 0;
        }
    }

    // On vient actualiser l'affichage des données des joueurs et des mines
    DisplayPlayersTurnName(PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerName());
    InitialisePlayersDisplay();
    InitialiseMinesDisplay();

    // On vient réactiver tous les boutons
    ReactivateAllButton();

    // On vient regarder si le joueur suivant n'a pas de mineur disponible
    if (PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->GetPlayerMiners() == 0)
    {
        // On vient désactiver tous les boutons
        DesactivateAllButton();

        // On vient afficher le message d'erreur
        SetCantPlayLabel("Vous n'avez pas de mineurs de disponible vous sautez donc votre tour.");
        QTimer::singleShot(1000, this, &MainWindow::NextTurn);

        return 0;
    }

    if (PartieEnCours->ListeJoueurs[PartieEnCours->TourJoueur]->IsBot())
    {
        MakeBotPlay();
    }

    return 0;
}

void MainWindow::MakeBotPlay()
{
    vector<Mine*> MineDispo;

    for (Mine* Mine : PartieEnCours->ListeMines)
    {
        if ((int)Mine->ListeMineursPresents.size() < Mine->CapaciteMax)
        {
            MineDispo.push_back(Mine);
        }
    }

    int RandomInt = PartieEnCours->GetRandomInt(0, MineDispo.size()-1);
    Mine* MineAEntrer = MineDispo[RandomInt];
    EnterMine(MineAEntrer->Numero);
}

void MainWindow::MakeMinersWork()
{
    for (int NumeroMine = 0; NumeroMine < 4; NumeroMine++)
    {
        // Je viens incrémenter le minage en cours seulement s'il y a au moins 1 mineur présent dans la mine
        if (PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents.size() > 0)
        {
            PartieEnCours->ListeMines[NumeroMine]->MinageEnCours++;

            // On vient actualiser l'affichage de la progress bar des mineurs qui minent
            int Numero = PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerNumber();
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
        if (PartieEnCours->ListeMines[NumeroMine]->MinageEnCours == PartieEnCours->ListeMines[NumeroMine]->DureeMinage)
        {
            if (PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->IsBot())
            {
                // Random int to make him win bonus coins
                HandleBonusCoinsCollected(NumeroMine, PartieEnCours->GetRandomInt(0, 12));
            }
            else
            {
                // On le fait jouer au mini jeu
                PlayMiniGame(NumeroMine);
            }
            // On remet le mineur dans le joueur ainsi que sa récompense
            PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->SetPlayerMiners(PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerMiners()+1);
            PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->SetPlayerCoins(PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerCoins() + PartieEnCours->ListeMines[NumeroMine]->Gain);

            // On vient ensuite réinitialiser la progress bar du mineur et la cacher
            int Numero = PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerNumber();
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
            PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents.erase(PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents.begin());

            // Puis on vient réinitialiser la variable MinageEnCours de la mine
            PartieEnCours->ListeMines[NumeroMine]->MinageEnCours = 0;
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
    ui->Player1Label->setText(QString::fromStdString(PartieEnCours->ListeJoueurs[0]->GetPlayerName()));
    ui->Player2Label->setText(QString::fromStdString(PartieEnCours->ListeJoueurs[1]->GetPlayerName()));
    ui->Player3Label->setText(QString::fromStdString(PartieEnCours->ListeJoueurs[2]->GetPlayerName()));
    ui->Player4Label->setText(QString::fromStdString(PartieEnCours->ListeJoueurs[3]->GetPlayerName()));

    ui->Player1Score->setText(QString::number(PartieEnCours->ListeJoueurs[0]->GetPlayerCoins()));
    ui->Player2Score->setText(QString::number(PartieEnCours->ListeJoueurs[1]->GetPlayerCoins()));
    ui->Player3Score->setText(QString::number(PartieEnCours->ListeJoueurs[2]->GetPlayerCoins()));
    ui->Player4Score->setText(QString::number(PartieEnCours->ListeJoueurs[3]->GetPlayerCoins()));

    ui->Player1MinerAvailable->setText(QString::number(PartieEnCours->ListeJoueurs[0]->GetPlayerMiners()));
    ui->Player2MinerAvailable->setText(QString::number(PartieEnCours->ListeJoueurs[1]->GetPlayerMiners()));
    ui->Player3MinerAvailable->setText(QString::number(PartieEnCours->ListeJoueurs[2]->GetPlayerMiners()));
    ui->Player4MinerAvailable->setText(QString::number(PartieEnCours->ListeJoueurs[3]->GetPlayerMiners()));
}

void MainWindow::InitialiseMinesDisplay()
{
    ui->Mine1Title->setText(QString::fromStdString(PartieEnCours->ListeMines[0]->Nom));
    ui->Mine2Title->setText(QString::fromStdString(PartieEnCours->ListeMines[1]->Nom));
    ui->Mine3Title->setText(QString::fromStdString(PartieEnCours->ListeMines[2]->Nom));
    ui->Mine4Title->setText(QString::fromStdString(PartieEnCours->ListeMines[3]->Nom));

    ui->Mine1CurrentMiners->setText(QString::number(PartieEnCours->ListeMines[0]->ListeMineursPresents.size()));
    ui->Mine2CurrentMiners->setText(QString::number(PartieEnCours->ListeMines[1]->ListeMineursPresents.size()));
    ui->Mine3CurrentMiners->setText(QString::number(PartieEnCours->ListeMines[2]->ListeMineursPresents.size()));
    ui->Mine4CurrentMiners->setText(QString::number(PartieEnCours->ListeMines[3]->ListeMineursPresents.size()));

    ui->Mine1TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours->ListeMines[0]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine2TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours->ListeMines[1]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine3TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours->ListeMines[2]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
    ui->Mine4TotalMiners->setText(QString::fromStdString(" / ") + QString::number(PartieEnCours->ListeMines[3]->CapaciteMax) + QString::fromStdString(" mineurs maximum"));
}

void MainWindow::DesactivateAllButton()
{
    ui->Mine1Enter->setDisabled(true);
    ui->Mine2Enter->setDisabled(true);
    ui->Mine3Enter->setDisabled(true);
    ui->Mine4Enter->setDisabled(true);
    ui->LeaveGameBtn->setDisabled(true);
}

void MainWindow::ReactivateAllButton()
{
    ui->Mine1Enter->setEnabled(true);
    ui->Mine2Enter->setEnabled(true);
    ui->Mine3Enter->setEnabled(true);
    ui->Mine4Enter->setEnabled(true);
    ui->LeaveGameBtn->setEnabled(true);
}

void MainWindow::ShowProgressBar(QProgressBar* ProgressBar)
{
    ProgressBar->setHidden(false);
}

void MainWindow::UpdateProgressBar(QProgressBar* ProgressBar, int NumeroMine)
{
    if (ProgressBar->maximum() != PartieEnCours->ListeMines[NumeroMine]->DureeMinage)
    {
        // On vient initialiser sa valeur max
        ProgressBar->setMaximum(PartieEnCours->ListeMines[NumeroMine]->DureeMinage);
    }

    // On incrémente sa valeur de 1
    ProgressBar->setValue(PartieEnCours->ListeMines[NumeroMine]->MinageEnCours);
}

void MainWindow::ClearAndHideProgressBar(QProgressBar* ProgressBar)
{
    ProgressBar->setHidden(true);
    ProgressBar->setValue(0);
}

void MainWindow::ClearGame(bool Redirect, int PageToRedirectTo)
{
    // Rompre les connexions des boutons de la mine et du bouton "LeaveGameBtn"
    disconnect(ui->Mine1Enter, &QPushButton::clicked, this, nullptr);
    disconnect(ui->Mine2Enter, &QPushButton::clicked, this, nullptr);
    disconnect(ui->Mine3Enter, &QPushButton::clicked, this, nullptr);
    disconnect(ui->Mine4Enter, &QPushButton::clicked, this, nullptr);
    disconnect(ui->LeaveGameBtn, &QPushButton::clicked, this, nullptr);

    // On vient supprimer le pointeur vers la PartieEnCours
    if (PartieEnCours)
    {
        delete PartieEnCours;
        PartieEnCours = nullptr;  // Important pour éviter l'accès à la mémoire libérée
    }

    // On redirige le joueur si nécessaire
    if (Redirect)
    {
        SwitchPages(PageToRedirectTo);
    }
}

bool ComparePair(const pair<Player*, int>& first, const pair<Player*, int>& second)
{
    return first.second > second.second;
}

void MainWindow::DisplayScoreBoard()
{
    vector<pair<Player*, int>> ScoreBoard(4);
    ScoreBoard[0] = make_pair(PartieEnCours->ListeJoueurs[0], PartieEnCours->ListeJoueurs[0]->GetPlayerCoins());
    ScoreBoard[1] = make_pair(PartieEnCours->ListeJoueurs[1], PartieEnCours->ListeJoueurs[1]->GetPlayerCoins());
    ScoreBoard[2] = make_pair(PartieEnCours->ListeJoueurs[2], PartieEnCours->ListeJoueurs[2]->GetPlayerCoins());
    ScoreBoard[3] = make_pair(PartieEnCours->ListeJoueurs[3], PartieEnCours->ListeJoueurs[3]->GetPlayerCoins());

    sort(ScoreBoard.begin(), ScoreBoard.end(), ComparePair);

    ui->FirstPlaceLabel->setText(QString::fromStdString("#1 -> ") + QString::fromStdString(ScoreBoard[0].first->GetPlayerName()) + QString::fromStdString(": ") + QString::number(ScoreBoard[0].first->GetPlayerCoins()) + QString::fromStdString(" 🪙"));
    ui->SecondPlaceLabel->setText(QString::fromStdString("#2 -> ") + QString::fromStdString(ScoreBoard[1].first->GetPlayerName()) + QString::fromStdString(": ") + QString::number(ScoreBoard[1].first->GetPlayerCoins()) + QString::fromStdString(" 🪙"));
    ui->ThirdPlaceLabel->setText(QString::fromStdString("#3 -> ") + QString::fromStdString(ScoreBoard[2].first->GetPlayerName()) + QString::fromStdString(": ") + QString::number(ScoreBoard[2].first->GetPlayerCoins()) + QString::fromStdString(" 🪙"));
    ui->FourthPlaceLabel->setText(QString::fromStdString("#4 -> ") + QString::fromStdString(ScoreBoard[3].first->GetPlayerName()) + QString::fromStdString(": ") + QString::number(ScoreBoard[3].first->GetPlayerCoins()) + QString::fromStdString(" 🪙"));

    ClearGame(false, 0);

    connect(ui->ReturnMenuBtn, &QPushButton::clicked, this, [this]{ SwitchPages(0); });
    connect(ui->ReplayBtn, &QPushButton::clicked, this, &MainWindow::StartGame);
}

void MainWindow::GetAndCreatePlayersInfo()
{
    int NumberOfPlayer = ui->NumberOfPlayersValue->currentText().toInt();
    string PlayerName1 = ui->PlayerNameValue1->text().toStdString();
    string PlayerName2 = ui->PlayerNameValue2->text().toStdString();
    string PlayerName3 = ui->PlayerNameValue3->text().toStdString();
    string PlayerName4 = ui->PlayerNameValue4->text().toStdString();
    string PlayerNames[4] = {PlayerName1, PlayerName2, PlayerName3, PlayerName4};
    PartieEnCours->CreateListeJoueurs(NumberOfPlayer, PlayerNames);
}

int MainWindow::PlayMiniGame(int NumeroMine)
{
    Minijeu *mj = new Minijeu(this);
    connect(mj, &Minijeu::BonusCoinsCollected, this, [=](int BonusCoins) { HandleBonusCoinsCollected(NumeroMine, BonusCoins); });

    return mj->exec();
}

void MainWindow::HandleBonusCoinsCollected(int NumeroMine, int BonusCoins)
{
    PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->SetPlayerCoins(PartieEnCours->ListeMines[NumeroMine]->ListeMineursPresents[0]->GetPlayerCoins() + BonusCoins);
}
