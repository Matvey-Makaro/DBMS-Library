#include "dao.h"

#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <exception>
#include <cassert>

DAO::DAO() :
    db_name("library"), db_user_name("root"), db_host_name("localhost"), db_password("admin")
{

    createConnection();
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
}

bool DAO::authorize(Role role, const QString& login, const QString& password)
{
    QString role_str, role_id_str, table_str;
    if(role == Role::ADMIN)
    {
        role_str = "ADMIN";
        role_id_str = "administrator_id";
        table_str = "Аdministrators";
    }
    else if(role == Role::LIBRARIAN)
    {
        role_str = "LIBRARIAN";
        role_id_str = "librarian_id";
        table_str = "Librarians";
    }
    else assert(0);

    QSqlQuery query;
    QString query_str_template = "SELECT %1 FROM %2 WHERE login=\'%3\' AND password=\'%4\';";
    make_query(query, query_str_template.arg(role_id_str).arg(table_str).arg(login).arg(password));

    qDebug() << query.size() << '\n';
    if(query.size() == 0)
        return false;
    assert(query.size() == 1);

    query.next();
    id = query.value(role_id_str).toInt();
    qDebug() << id << '\n';
    make_query(query, QString("SET @CUR_ID=%1").arg(id));
    make_query(query, QString("SET @CUR_ROLE=\'%1\'").arg(role_str));



    return true;
}

bool DAO::createConnection()
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
}

void DAO::make_query(QSqlQuery& query,  const QString& query_str)
{
    if (!query.exec(query_str))
        throw std::runtime_error("Query error!" + query.lastError().text().toStdString());
}
