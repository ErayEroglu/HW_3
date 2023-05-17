#include "mainwindow.h"
#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scoreLabel = new QLabel("Score :");
    triesLabel = new QLabel("Number of tries remaining");
    newGameButton = new QPushButton(tr("New Game "));
    // TODO: there should be a connect button to check if the user clicked the new game
    // to do this, restarting the game logic should be implemented


    // creates cards as ?
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 6; column++)
        {
            cardButtons[row][column] = new QPushButton(tr("?"));
            // TODO: connect function for clicking
            // card flipping logic should be implemented before
        }

    }

    // creates the widgets for cards
    QGridLayout *middle = new QGridLayout;
    for (int row = 0; row < 6; row++)
    {
        for (int column = 0; column < 5; column++)
        {
            middle->addWidget(cardButtons[row][column], row, column);
        }
    }


    // the layout which is consisted of score and remaining try parts
    QHBoxLayout* top = new QHBoxLayout;
    top->addWidget(scoreLabel);
    top->addWidget(triesLabel);
    top->addStretch();
    top->addWidget(newGameButton);

    // main layout, merges all layouts
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(top);
    mainLayout->addLayout(middle);

    // Set the main layout
    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    setWindowTitle(tr("Pairs"));

}

void newGame()
{
    // TODO
}


void cardClicked()
{
    // TODO
}





















