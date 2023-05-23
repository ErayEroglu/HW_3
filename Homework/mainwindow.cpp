#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <random>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    scoreLabel = new QLabel("Score :");  // creates score label
    currentScore = new QLabel(QString::number(score));
    triesLabel = new QLabel("Number of tries remaining :");  // creates number of remaining try label
    currentTries = new QLabel(QString::number(triesRemaining));
    newGameButton = new QPushButton(tr("New Game "));
    connect(newGameButton,SIGNAL(clicked()),this,SLOT(newGame()));  // connects button signals with functions

    QHBoxLayout* top = new QHBoxLayout;  // creates the layout and necessary widgets in this layout
    top->addWidget(scoreLabel);
    top->addWidget(currentScore);
    top->addWidget(triesLabel);
    top->addWidget(currentTries);
    top->addStretch();
    top->addWidget(newGameButton);

    int counter = 1;
    for (int row = 0; row < 5; row++)  // creates cards as buttons and stores them in array
    {
        for (int column = 0; column < 6; column++)
        {
            cardButtons[row][column] = new QPushButton(tr("?"));  // player will see the closed cards as ?
            cardButtons[row][column]->setProperty("row",row);
            cardButtons[row][column]->setProperty("column",column);
            cardButtons[row][column]->setProperty("key",(31-counter)*counter);
            cardButtons[row][column]->setProperty("state","closed");
            QObject::connect(cardButtons[row][column], &QPushButton::clicked, this, [this, row, column]() {
                cardFlip(cardButtons[row][column]);  // connects functions with signals
            });

            counter++;
        }


    }

    QGridLayout *middle = new QGridLayout;
    for (int row = 0; row < 5; row++)  // creates card widgets
    {
        for (int column = 0; column < 6; column++)
        {
            middle->addWidget(cardButtons[row][column], row, column);
        }
    }

    // shuffles cards
    newGame();


    // main layout, merges all layouts
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(top);
    mainLayout->addLayout(middle);

    // creates game widget, set window title and size
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

void MainWindow::newGame()  // if player wants to restart the game, shuffles cards and set the initial values for buttons
{
    score = 0;
    triesRemaining = 50;
    currentScore->setText(QString::number(score));
    currentTries->setText(QString::number(triesRemaining));

    vector<coordinate> usedPositions;
    coordinate currCoor;
    bool flag = true;
    int counter = 1;

    for (int row = 0;row < 5;row++)
    {
        for(int column = 0; column < 6 ;column++)
        {
            while (flag)  // shuffles cards
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

    for (int row = 0;row < 5;row++)  // set initial values of card properties
    {
        for(int column = 0;column<6;column++)
        {
            cardButtons[row][column]->setText("?");
            cardButtons[row][column]->setProperty("state","closed");
        }
    }

}


void MainWindow::cardFlip(QPushButton* card)  // when player clickes a card, show its value
{
    if(card->property("state")=="closed" && triesRemaining > 0 && score < 50){  // the player can flip cards if s/he has a remaining try
        if(openCards == 0){                                                     // or there are closed cards
            card->setText(card->property("key").toString());
            openCards++;
            openedCard = card;
            return;
        }
        if(openCards == 1){
            if(card == openedCard){
                return;
            }

            if(openedCard->property("key") == card->property(("key"))){  // if player matches 2 cards, increase his/her score
                card->setText(card->property("key").toString());
                openCards = 0;
                score += 2;
                currentScore->setText(QString::number(score));
                triesRemaining -= 1;
                currentTries->setText(QString::number(triesRemaining));
                card->setProperty("state","opened");
                openedCard->setProperty("state","opened");
                return;
            }
            card->setText(card->property("key").toString());
            triesRemaining -= 1;
            currentTries->setText(QString::number(triesRemaining));
            openCards ++;
            // timer to close the cards after 1 second
            QTimer::singleShot(1000, [this, card]() {
                openedCard->setText("?");
                card->setText("?");
                openCards = 0;
            });
            return;
        }
    }
    return;
}

// helper functions

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
            return true; // Element found in the vector
        }
    }
    return false; // Element not found in the vector
}
