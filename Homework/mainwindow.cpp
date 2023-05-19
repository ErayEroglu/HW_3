#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <random>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    scoreLabel = new QLabel("Score :");
    currentScore = new QLabel(QString::number(score));
    triesLabel = new QLabel("Number of tries remaining :");
    currentTries = new QLabel(QString::number(triesRemaining));
    newGameButton = new QPushButton(tr("New Game "));
    connect(newGameButton,SIGNAL(clicked()),this,SLOT(newGame()));

    QHBoxLayout* top = new QHBoxLayout;
    top->addWidget(scoreLabel);
    top->addWidget(currentScore);
    top->addWidget(triesLabel);
    top->addWidget(currentTries);
    top->addStretch();
    top->addWidget(newGameButton);

    int counter = 1;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 6; column++)
        {
            cardButtons[row][column] = new QPushButton(tr("?"));
            cardButtons[row][column]->setProperty("row",row);
            cardButtons[row][column]->setProperty("column",column);
            cardButtons[row][column]->setProperty("key",(31-counter)*counter);
            QObject::connect(cardButtons[row][column], &QPushButton::clicked, this, [this, row, column]() {
                cardFlip(cardButtons[row][column]);
            });

            counter++;
        }


    }

    QGridLayout *middle = new QGridLayout;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 6; column++)
        {
            middle->addWidget(cardButtons[row][column], row, column);
        }
    }



    // main layout, merges all layouts
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(top);
    mainLayout->addLayout(middle);


    QWidget* gameWidget = new QWidget(this);
    gameWidget->setLayout(mainLayout);
    setCentralWidget(gameWidget);

    setWindowTitle(tr("Pairs"));
    setFixedHeight(sizeHint().height());
    gameWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    score = 0;
    triesRemaining = 50;
    currentScore->setText(QString::number(score));
    currentTries->setText(QString::number(triesRemaining));
    vector<coordinate> usedPositions;
    coordinate currCoor;
    bool flag = true;
    int counter = 1;
    int tempRow = 0;
    int tempCol = 0;

    for (int row = 0;row < 5;row++)
    {
        for(int column = 0; column < 6 ;column++)
        {
            while (flag)
            {
                currCoor.x = static_cast<int> (randomGenerator() * 6);
                currCoor.y = static_cast<int> (randomGenerator() * 5);

                if (!doesContain(usedPositions,currCoor))
                {
                    usedPositions.push_back(currCoor);
                    flag = false;
                }

            }
            cardButtons[currCoor.y][currCoor.x]->setProperty("key",(31 - counter) * counter);
            counter++;
            flag = true;
        }
    }

    for (int row = 0;row < 5;row++)
    {
        for(int column = 0;column<6;column++)
        {
            cardButtons[row][column]->setText("?");
        }
    }

}


void MainWindow::cardFlip(QPushButton* card)
{
    if(openCards == 0)
    {
        card->setText(card->property("key").toString());
        openCards++;
        openedCard = card;
        return;
    }
    if(openCards == 1)
    {
        if(openedCard->property("key") == card->property(("key")))
        {
            card->setText(card->property("key").toString());
            openCards = 0;
            score += 2;
            currentScore->setText(QString::number(score));
            return;
        }
        openedCard->setText("?");
        openCards = 0;
        triesRemaining -=1;
        currentTries->setText(QString::number(triesRemaining));
        return;
    }
    return;
    // TODO
}


// generates random floats between 0 and 1
float MainWindow::randomGenerator()
{
    return (float) rand() / RAND_MAX;
}


bool MainWindow::doesContain(vector<coordinate> arr,coordinate coor) {
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].x == coor.x && arr[i].y == coor.y)
        {
            return true; // Element found in the array
        }
    }
    return false; // Element not found in the array
}
