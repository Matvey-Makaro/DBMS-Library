#ifndef DAO_H
#define DAO_H

#include "models.h"

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

class DAO
{
public:
    DAO();

    bool authorize(Role role, const QString& login, const QString& password);
    QSqlQueryModel& show_all_books_for_librarian();
    void add_book(const BookInfo& book_info);
    QSqlQueryModel& find_book_by_name(const QString& book_name);
    QSqlQueryModel& show_booked_book_by_reader_id(int r_id);
    QSqlQueryModel& show_booked_book();
    void lend_book(int b_id, int r_id);
    QSqlQueryModel& show_all_books_for_reader();
    bool authorize_reader(const QString& name, const QString& surname, const QString& number);
    void book_book(int b_id);
    void cancle_booking(int r_id, int b_id);
    void cancle_booking(int b_id);
    QSqlQueryModel& show_taken_books(int r_id);
    QSqlQueryModel& show_taken_books();
    QSqlQueryModel& show_debtor_books(int r_id);
    QSqlQueryModel& show_debtor_books();
    QSqlQueryModel& show_all_librarians();
    void create_librarian(const LibrarianInfo& librarian_info);
    void update_librarian(int librarian_id, const LibrarianInfo& librarian_info);
    void delete_librarian(int librarian_id);

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
