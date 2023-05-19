#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <string>

typedef struct
{
    int x;
    int y;
} coordinate;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    float randomGenerator();
    bool doesContain(std::vector<coordinate> arr,coordinate coor);

private:
    Ui::MainWindow *ui;
    QLabel *scoreLabel;
    QLabel *triesLabel;
    QLabel *currentScore;
    QLabel *currentTries;
    QPushButton *newGameButton;
    QPushButton *cardButtons[5][6];
    int triesRemaining = 50;
    int score = 0;
    int openCards = 0;
    QPushButton* openedCard;
private slots:
    void newGame();
    void cardFlip(QPushButton* card);
};
#endif // MAINWINDOW_H
