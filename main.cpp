#include "mainwindow.h"
#include "dao.h"

#include <QApplication>
#include <QCryptographicHash>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DAO dao;

    QByteArray hash = QCryptographicHash::hash("fedotova", QCryptographicHash::Sha256);
    QString hashed_password = QString(hash.toHex());

    qDebug() << "Hashed password: " << hashed_password << '\q';
    qDebug() << hashed_password.size();

    MainWindow w(dao);
    w.show();
    return a.exec();
}
