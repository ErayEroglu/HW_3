#include "mainwindow.h"
#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scoreLabel = new QLabel("Score :");
    triesLabel = new QLabel("Number of tries remaining :");
    newGameButton = new QPushButton(tr("New Game "));
    connect(newGameButton,SIGNAL(clicked()),this,SLOT(newGame()));

    // creates cards as ?
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 6; column++)
        {
            cardButtons[row][column] = new QPushButton(tr("?"));
            cardButtons[row][column]->setProperty("row",row);
            cardButtons[row][column]->setProperty("column",column);
            connect(cardButtons[row][column],SIGNAL(clicked()),this,SLOT(cardFlip()));
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

    QWidget* gameWidget = new QWidget(this);
    gameWidget->setLayout(mainLayout);
    setCentralWidget(gameWidget);

    setWindowTitle(tr("Pairs"));
    setFixedHeight(sizeHint().height());
}

void MainWindow::newGame()
{
    // TODO
    cout << "stop";
}


void MainWindow::cardFlip()
{
    cout << "flip";
    // TODO
}
