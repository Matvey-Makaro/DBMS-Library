#include "dao.h"

#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>

DAO::DAO() :
    db_name("library"), db_user_name("root"), db_host_name("localhost"), db_password("admin")
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(db_name);
    db.setUserName(db_user_name);
    db.setHostName(db_host_name);
    db.setPassword(db_password);
    db.setPort(3306);

    if(!db.open())
    {
        qDebug() << "Cannot open database:"  << db.lastError() << '\n';
    }

    QSqlQuery query;
//    QString str1 = "SET @CUR_ID = 1;";
//    if (!query.exec(str1))
//    {
//        qDebug() << "Query error!" << query.lastError();
//    }
//    QString str2 = "SET @CUR_ROLE = \"LIBRARIAN\"";
//    if (!query.exec(str2))
//    {
//        qDebug() << "Query error!" << query.lastError();
//    }
//    QString str = "INSERT INTO Rooms(name) VALUES ('Room 7');";

//    if (!query.exec(str))
//    {
//        qDebug() << "Query error!" << query.lastError();
//    }


    QString str = "SELECT * FROM Rooms;";
    if (!query.exec(str))
    {
        qDebug() << "Query error!" << query.lastError();
    }
    QSqlRecord rec = query.record();
    qDebug() << query.size();
    query.next();
    qDebug() << query.value("name").toString();


    QStringList lst = db.tables(QSql::TableType::SystemTables);
    for(const auto& i : lst)
    {
        qDebug() << "Table: " << i << '\n';
    }
}
