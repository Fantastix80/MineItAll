#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void DisplayCurrentRound(int CurrentRound);
    void SetCantPlayLabel(string Message);
    void DisplayCurrentRound(Player* ListeJoueurs[4]);
    void DisplayPlayersTurnName(string PlayerName);
    void EnterMine(int MineAEntrer);
    void InitialisePlayersDisplay();
    void InitialiseMinesDisplay();

private:
    Ui::MainWindow *ui;
    Partie PartieEnCours;
};
#endif // MAINWINDOW_H
