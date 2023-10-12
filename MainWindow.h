#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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

    void ActionTimer();
    void DisplayCurrentRound(int CurrentRound);
    void SetCantPlayLabel(string Message);
    void ClearCantPlayLabel();
    void DisplayCurrentRound(Player* ListeJoueurs[4]);
    void DisplayPlayersTurnName(string PlayerName);
    int EnterMine(int MineAEntrer);
    void NextTurn();
    void MakeMinersWork();
    void DesactivateAllButton();
    void ReactivateAllButton();
    void InitialisePlayersDisplay();
    void InitialiseMinesDisplay();
    void ShowProgressBar(QProgressBar* ProgressBar);
    void UpdateProgressBar(QProgressBar* ProgressBar, int NumeroMine);
    void ClearAndHideProgressBar(QProgressBar* ProgressBar);

private:
    Ui::MainWindow *ui;
    Partie PartieEnCours;
    QTimer* Timer;
};
#endif // MAINWINDOW_H
