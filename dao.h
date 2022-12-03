#ifndef DAO_H
#define DAO_H

#include <QSqlDatabase>
#include <QString>

class DAO
{
public:
    DAO();

private:
    bool createConnection();

private:
    QSqlDatabase db;
    QString db_name;
    QString db_user_name;
    QString db_host_name;
    QString db_password;
};

#endif // DAO_H
