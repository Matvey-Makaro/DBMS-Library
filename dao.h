#ifndef DAO_H
#define DAO_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <memory>

enum class Role
{
    READER,
    LIBRARIAN,
    ADMIN
};

struct BookInfo
{
    QString book_name;
    QString author_name;
    QString author_surname;
    QString author_patronymic;
    QString author_pseudonym;
    int publication_year;
    QString publisher_name;
    QString isbn;
    int amount;
};

class DAO
{
public:
    DAO();

    bool authorize(Role role, const QString& login, const QString& password);
    QSqlQueryModel& show_all_books_for_librarian();
    void add_book(const BookInfo& book_info);
    QSqlQueryModel& find_book_by_name(const QString& book_name);
    QSqlQueryModel& show_booked_book_by_reader_id(int r_id);
    void lend_book(int b_id, int r_id);
private:
    bool createConnection();
    void make_query(QSqlQuery& query, const QString& query_str);

private:
    QSqlDatabase db;
    QString db_name;
    QString db_user_name;
    QString db_host_name;
    QString db_password;
    std::unique_ptr<QSqlQueryModel> model;
    Role role;
    int id;


};

#endif // DAO_H
