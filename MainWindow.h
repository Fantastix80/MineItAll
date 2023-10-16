#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include "Player.h"
#include "Partie.h"
#include <string>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SwitchPages(int Index);
    void QuitGame();
    void StartGame();
    void DisplayCurrentRound(int CurrentRound);
    void SetCantPlayLabel(string Message);
    void ClearCantPlayLabel();
    void DisplayCurrentRound(Player* ListeJoueurs[4]);
    void DisplayPlayersTurnName(string PlayerName);
    int EnterMine(int MineAEntrer);
    int NextTurn();
    void MakeBotPlay();
    void MakeMinersWork();
    void DesactivateAllButton();
    void ReactivateAllButton();
    void InitialisePlayersDisplay();
    void InitialiseMinesDisplay();
    void ShowProgressBar(QProgressBar* ProgressBar);
    void UpdateProgressBar(QProgressBar* ProgressBar, int NumeroMine);
    void ClearAndHideProgressBar(QProgressBar* ProgressBar);
    void ClearGame(bool Redirect, int PageToRedirectTo);
    void DisplayScoreBoard();
    void GetAndCreatePlayersInfo();
    int PlayMiniGame(int NumeroMine);
    void HandleBonusCoinsCollected(int NumeroMine, int BonusCoins);

public slots:
    void Options(QString NumberOfPlayers);

private:
    Ui::MainWindow *ui;
    Partie* PartieEnCours;
    int ScoreMiniJeu;
};
#endif // MAINWINDOW_H
