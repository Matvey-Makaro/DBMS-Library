#include "mainwindow.h"
#include "dao.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DAO dao;

    MainWindow w;
    w.show();
    return a.exec();
}
