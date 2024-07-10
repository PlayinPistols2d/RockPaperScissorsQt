#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "computerai.h"
#include "qlabel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum gameResults {
        draw,
        computerWon,
        playerWon
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_rock_clicked();

    void on_pb_paper_clicked();

    void on_pb_scissors_clicked();

private:
    Ui::MainWindow *ui;
    ComputerAi* computer;
    //Player* player; could be usefull for simple tcp multiplayer game

    QString playerWonMessage = "You won !";
    QString computerWonMessage = "Computer Won !";
    QString drawMessage = "It’s a draw !";
    QString resetMessage = "Score was reset !";

    int localPlayerScore;
    int localComputerScore;

    void playGame(gameOptions playerDescision);
    gameResults determineWinner(gameOptions playerDescision, gameOptions computerDescision);
    void handleDraw();
    void handleComputerWon();
    void handlePlayerWon();
    void updateScore();
    void animateChoice(QLabel* label, const QString &imagePath);
    void playPreAnimation(gameOptions playerDescision, gameOptions computerDescision);
    void setButtonsEnabled(bool state);
    void resetScore();
};
#endif // MAINWINDOW_H
