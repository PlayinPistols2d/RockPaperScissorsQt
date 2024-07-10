#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+R"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::resetScore);
    computer = new ComputerAi();
    //player = new Player(); could be usefull for simple tcp multiplayer game
    localComputerScore=0;
    localPlayerScore=0;
    setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_rock_clicked()
{
    playGame(rock);
}


void MainWindow::on_pb_paper_clicked()
{
    playGame(paper);
}


void MainWindow::on_pb_scissors_clicked()
{
    playGame(scissors);
}

void MainWindow::playGame(gameOptions playerDescision)
{
    setButtonsEnabled(false);
    gameOptions computerDescision = computer->makeDescision();

    playPreAnimation(playerDescision, computerDescision);

    if(determineWinner(playerDescision, computerDescision) == draw) {
        handleDraw();
    } else if(determineWinner(playerDescision, computerDescision) == computerWon) {
        handleComputerWon();
    } else if(determineWinner(playerDescision, computerDescision) == playerWon) {
        handlePlayerWon();
    }
    updateScore();
}

MainWindow::gameResults MainWindow::determineWinner(gameOptions playerDescision, gameOptions computerDescision)
{
    if(playerDescision == computerDescision ) {
        return draw;
    }
    if((playerDescision == rock && computerDescision == scissors) ||
        (playerDescision == paper && computerDescision == rock) ||
        (playerDescision == scissors && computerDescision == paper)) {
            return playerWon;
    }
    return computerWon;
}

void MainWindow::handleDraw()
{
    ui->lb_resultMessage->setText(drawMessage);
}

void MainWindow::handleComputerWon()
{
    ui->lb_resultMessage->setText(computerWonMessage);
    localComputerScore++;
}

void MainWindow::handlePlayerWon()
{
    ui->lb_resultMessage->setText(playerWonMessage);
    localPlayerScore++;
}

void MainWindow::updateScore()
{
    ui->lcd_computerScore->display(localComputerScore);
    ui->lcd_playerScore->display(localPlayerScore);
}

void MainWindow::animateChoice(QLabel *label, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    label->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));

    QRect startRect = label->geometry();
    QRect endRect = startRect;
    endRect.moveTop(startRect.top() - 10);

    // Move up animation
    QPropertyAnimation *moveUpAnimation = new QPropertyAnimation(label, "geometry");
    moveUpAnimation->setDuration(500);
    moveUpAnimation->setStartValue(startRect);
    moveUpAnimation->setEndValue(endRect);
    moveUpAnimation->setEasingCurve(QEasingCurve::OutBounce);

    // Move back to original position
    QPropertyAnimation *moveBackAnimation = new QPropertyAnimation(label, "geometry");
    moveBackAnimation->setDuration(500);
    moveBackAnimation->setStartValue(endRect);
    moveBackAnimation->setEndValue(startRect);
    moveBackAnimation->setEasingCurve(QEasingCurve::OutBounce);

    // Sequential animation group
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
    group->addAnimation(moveUpAnimation);
    group->addAnimation(moveBackAnimation);
    // Re-enable buttons after animation
    connect(group, &QSequentialAnimationGroup::finished, this, [this]() {
        setButtonsEnabled(true);
    });
    group->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::playPreAnimation(gameOptions playerDescision, gameOptions computerDescision)
{
    QString tempPath;
    if(playerDescision == rock) {
        tempPath = ":/resources/rock.png";
    } else if(playerDescision == paper) {
        tempPath = ":/resources/paper.png";
    } if(playerDescision == scissors) {
        tempPath = ":/resources/scissors.png";
    }
    animateChoice(ui->_playerDecisionImg, tempPath);
    if(computerDescision == rock) {
        tempPath = ":/resources/rock.png";
    } else if(computerDescision == paper) {
        tempPath = ":/resources/paper.png";
    } if(computerDescision == scissors) {
        tempPath = ":/resources/scissors.png";
    }
    animateChoice(ui->_computerDecisionImg, tempPath);
}

void MainWindow::setButtonsEnabled(bool state)
{
    ui->pb_rock->setEnabled(state);
    ui->pb_paper->setEnabled(state);
    ui->pb_scissors->setEnabled(state);
}

void MainWindow::resetScore()
{
    if(ui->pb_rock->isEnabled()) {
        localComputerScore = 0;
        localPlayerScore = 0;
        updateScore();
        ui->lb_resultMessage->setText(resetMessage);
    }
}

