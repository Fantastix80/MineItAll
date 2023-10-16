#ifndef MINIJEU_H
#define MINIJEU_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Minijeu;
}

class Minijeu : public QDialog
{
    Q_OBJECT

public:
    explicit Minijeu(QWidget *parent = nullptr);
    ~Minijeu();

private:
    // Variables
    Ui::Minijeu *ui;
    QTimer* Timer;
    int TempsMinijeu;
    int CompteARebours;
    int CoinsCounter;

    // Fonctions
    void TimerMinijeu();
    void TimerCompteARebours();
    void StartMiniGame();
    void ShowRandomButton();
    void HideClickedButton(int row, int column);
    void HandleButtonClick(int row, int column);
    void DesactivateAllButtons();
    void MiniGameFinished();

signals:
    void BonusCoinsCollected(int numberOfCoins);
};

#endif // MINIJEU_H
