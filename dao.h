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
    void delete_book(int book_id);
    QSqlQueryModel& find_book_by_name(const QString& book_name);
    QSqlQueryModel& show_booked_book_by_reader_id(int r_id);
    QSqlQueryModel& show_booked_book();
    void lend_book(int b_id, int r_id);
    QSqlQueryModel& show_all_books_for_reader();
    bool authorize_reader(const QString& name, const QString& surname, const QString& number);
    void book_book(int b_id);
    void cancle_booking(int r_id, int b_id);
    void cancle_booking(int b_id);
    void accept_book_from_reader(int book_id, int reader_id);
    QSqlQueryModel& show_taken_books(int r_id);
    QSqlQueryModel& show_taken_books();
    QSqlQueryModel& show_debtor_books(int r_id);
    QSqlQueryModel& show_debtor_books();
    QSqlQueryModel& show_all_librarians();
    void create_librarian(const LibrarianInfo& librarian_info);
    void update_librarian(int librarian_id, const LibrarianInfo& librarian_info);
    void delete_librarian(int librarian_id);
    QSqlQueryModel& show_all_rooms();
    void create_room(const RoomInfo& room_info);
    void update_room(int room_id, const RoomInfo& room_info);
    void delete_room(int room_id);
    QSqlQueryModel& show_all_readers();
    void create_reader(const ReaderInfo& reader_info);
    void update_reader(int reader_id, const ReaderInfo& reader_info);
    void delete_reader(int reader_id);
    QSqlQueryModel& show_all_debtors();

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

    int MAX_BOOKED_BOOKS_FOR_READER = 5;

};

#endif // DAO_H
