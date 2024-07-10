#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/rock.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
