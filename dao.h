#ifndef DAO_H
#define DAO_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

enum class Role
{
    READER,
    LIBRARIAN,
    ADMIN
};

class DAO
{
public:
    DAO();

    bool authorize(Role role, const QString& login, const QString& password);

private:
    bool createConnection();
    void make_query(QSqlQuery& query, const QString& query_str);

private:
    QSqlDatabase db;
    QString db_name;
    QString db_user_name;
    QString db_host_name;
    QString db_password;

    Role role;
    int id;


};

#endif // DAO_H
