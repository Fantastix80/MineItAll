#include "minijeu.h"
#include "ui_minijeu.h"
#include "windows.h"

#include <QPushButton>

Minijeu::Minijeu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Minijeu), Timer (new QTimer)
{
    ui->setupUi(this);

    // On vient cacher la progress bar
    ui->TimeProgressBar->hide();

    // On vient générer tous les boutons pour le mini-jeu
    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            QPushButton *button = new QPushButton("🪙");

            // On applique la bonne police et la bonne taille
            QFont font("Modern No. 20", 20);
            button->setFont(font);

            // On vient effectuer une manipulation qui permettra de conserver l'espace pris par le bouton dans le
            // grid layout même lorsqu'il sera caché
            QSizePolicy sp_retain = button->sizePolicy();
            sp_retain.setRetainSizeWhenHidden(true);
            button->setSizePolicy(sp_retain);
            button->hide();

            connect(button, &QPushButton::clicked, this, [this, row, column]{ HandleButtonClick(row, column); });
            ui->JeuContainer->addWidget(button, row, column);
        }
    }

    StartMiniGame();
}

Minijeu::~Minijeu()
{
    delete ui;
}

int GetRandomInt(int MinInt, int MaxInt)
{
    int TempInt = MaxInt - MinInt;
    int RandomInt = rand() % (TempInt + 1);
    int ResultInt = RandomInt + MinInt;

    return ResultInt;
}

void Minijeu::TimerMinijeu()
{
    TempsMinijeu++;
    if (TempsMinijeu != 5)
    {
        ui->TimeProgressBar->setValue(TempsMinijeu);
    }
    else
    {
        ui->TimeProgressBar->setValue(TempsMinijeu);
        Timer->stop();
        DesactivateAllButtons();
        MiniGameFinished();
    }
}

void Minijeu::TimerCompteARebours()
{
    CompteARebours--;
    if (CompteARebours != 0)
    {
        ui->StartTimeLabel->setText(QString::number(CompteARebours));
    }
    else
    {
        // On cache le le décompte
        ui->StartTimeLabel->hide();

        // On vient afficher la progress bar et l'activer
        ui->TimeProgressBar->show();
        ui->TimeProgressBar->setMaximum(5);
        ui->TimeProgressBar->setValue(0);

        // On arrête le Timer
        Timer->stop();

        // On lance un nouveau timer pour le endgame
        Timer->start(1000);
        connect(Timer, &QTimer::timeout, this, &Minijeu::TimerMinijeu);

        // On vient afficher un bouton aléatoire afin de commencer le minijeu
        ShowRandomButton();
    }
}

void Minijeu::StartMiniGame()
{
    TempsMinijeu = 0;
    CompteARebours = 3;
    CoinsCounter = 0;
    Timer->start(1000);
    connect(Timer, &QTimer::timeout, this, &Minijeu::TimerCompteARebours);
}

void Minijeu::ShowRandomButton()
{
    int row = GetRandomInt(0, 9);
    int column = GetRandomInt(0, 9);
    ui->JeuContainer->itemAtPosition(row, column)->widget()->show();
}

void Minijeu::HideClickedButton(int row, int column)
{
    ui->JeuContainer->itemAtPosition(row, column)->widget()->hide();
}

void Minijeu::HandleButtonClick(int row, int column)
{
    // On vient actualiser le compteur et afficher le nouveau score
    CoinsCounter++;
    ui->ScoreValue->setText(QString::number(CoinsCounter));

    HideClickedButton(row, column);
    ShowRandomButton();
}

void Minijeu::DesactivateAllButtons()
{
    for (int row = 0; row < 10; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            ui->JeuContainer->itemAtPosition(row, column)->widget()->setEnabled(false);
        }
    }
}

void Minijeu::MiniGameFinished()
{
    // On vient actualiser l'affichage des instructions
    std::string InstructionDeFin = "Bien joué ! Vous avez récupéré " + std::to_string(CoinsCounter) + " pièces bonus";
    ui->RulesLabel->setText(QString::fromStdString(InstructionDeFin));

    // On vient transmettre le score à la main window
    emit BonusCoinsCollected(CoinsCounter);

    // Ferme la fenêtre contenant le minijeu après 3 secondes
    QTimer::singleShot(3000, this, [this]{ accept(); });
}
