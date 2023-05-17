#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    QLabel *scoreLabel;
    QLabel *triesLabel;
    QPushButton *newGameButton;
    QPushButton *cardButtons[5][6];
    int triesRemaining = 50;
    int score = 0;

private slots:
   void newGame();
   void cardFlip();
};

#endif
