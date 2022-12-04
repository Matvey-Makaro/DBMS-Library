#include "dao.h"

#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <exception>
#include <cassert>
#include <utility>

DAO::DAO() :
    db_name("library"), db_user_name("root"), db_host_name("localhost"), db_password("admin")
{

    createConnection();
    model = std::unique_ptr<QSqlQueryModel>(new QSqlQueryModel);
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
        table_str = "Administrators";
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

QSqlQueryModel& DAO::show_all_books_for_librarian()
{
    model->setQuery("SELECT * FROM books_info");

    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

void DAO::add_book(const BookInfo &book_info)
{
    QString str_template = "CALL create_book('%1', '%2', '%3', '%4', '%5', %6, '%7', '%8', %9);";
    QString str;
    if(book_info.book_name.isEmpty())
        throw std::runtime_error("Book name can't be empty.");
    str = str_template.arg(book_info.book_name);

    if(book_info.author_name.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(book_info.author_name);

    if(book_info.author_surname.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(book_info.author_surname);

    if(book_info.author_patronymic.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(book_info.author_patronymic);

    if(book_info.author_pseudonym.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(book_info.author_pseudonym);

    str = str.arg(book_info.publication_year);

    if(book_info.publisher_name.isEmpty())
        throw std::runtime_error("Publisher name can't be empty.");
    str = str.arg(book_info.publisher_name);

    if(book_info.isbn.isEmpty())
        throw std::runtime_error("ISBN can't be empty.");
    str = str.arg(book_info.isbn);

    str = str.arg(book_info.amount);

    QSqlQuery query;
    make_query(query, str);
}

QSqlQueryModel &DAO::find_book_by_name(const QString &book_name)
{
    QString str_template = "SELECT * FROM books_info WHERE book_name=('%1')";
    model->setQuery(str_template.arg(book_name));

    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

QSqlQueryModel &DAO::show_booked_book_by_reader_id(int r_id)
{
    QString str_template("CALL get_booked_books_by_reader_id(%1)");
    model->setQuery(str_template.arg(r_id));
    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;

}

QSqlQueryModel &DAO::show_booked_book()
{
    return show_booked_book_by_reader_id(id);
}

void DAO::lend_book(int b_id, int r_id)
{
    QString str_template = "CALL lend_book(%1, %2);";
    QSqlQuery query;
    make_query(query, str_template.arg(b_id).arg(r_id));
}

QSqlQueryModel &DAO::show_all_books_for_reader()
{
    model->setQuery("SELECT * FROM books_info WHERE available_amount > 0");

    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

bool DAO::authorize_reader(const QString &name, const QString &surname, const QString &number)
{
    QString role_str = "READER", role_id_str = "reader_id", table_str="readers_info";

    QSqlQuery query;
    QString query_str_template = "SELECT %1 FROM %2 WHERE name=\'%3\' AND surname=\'%4\' AND number=\'%5\';";
    make_query(query, query_str_template.arg(role_id_str).arg(table_str).arg(name).arg(surname).arg(number));

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

void DAO::book_book(int b_id)
{
    QString str_template = "CALL book_book(%1);";
    QSqlQuery query;
    make_query(query, str_template.arg(b_id));
}

void DAO::cancle_booking(int r_id, int b_id)
{
    QString str_template = "CALL cancle_booking_book(%1, %2);";
    QSqlQuery query;
    make_query(query, str_template.arg(r_id).arg(b_id));
}

void DAO::cancle_booking(int b_id)
{
    cancle_booking(id, b_id);
}

QSqlQueryModel &DAO::show_taken_books(int r_id)
{
    QString str_template = "CALL get_reader_taken_books(%1)";
    model->setQuery(str_template.arg(r_id));
    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

QSqlQueryModel &DAO::show_taken_books()
{
    return show_taken_books(id);
}

QSqlQueryModel &DAO::show_debtor_books(int r_id)
{
    QString str_template = "CALL get_debtor_books_by_reader_id(%1)";
    model->setQuery(str_template.arg(r_id));
    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

QSqlQueryModel &DAO::show_debtor_books()
{
    return show_debtor_books(id);
}

QSqlQueryModel &DAO::show_all_librarians()
{
    model->setQuery("CALL get_all_librarians()");
    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

void DAO::create_librarian(const LibrarianInfo &librarian_info)
{
    QString str_template("CALL create_librarian('%1', '%2', '%3', '%4', '%5', %6, %7);");
    QString str;

    if(librarian_info.login.isEmpty())
        throw std::runtime_error("Login can't be empty.");
    str = str_template.arg(librarian_info.login);

    if(librarian_info.password.isEmpty())
        throw std::runtime_error("Password can't be empty.");
    str = str.arg(librarian_info.password);

    if(librarian_info.name.isEmpty())
        throw std::runtime_error("Name can't be empty.");
    str = str.arg(librarian_info.name);

    if(librarian_info.surname.isEmpty())
        throw std::runtime_error("Surname can't be empty.");
    str = str.arg(librarian_info.surname);

    if(librarian_info.patronymic.isEmpty())
        throw std::runtime_error("Patronymic can't be empty.");
    str = str.arg(librarian_info.patronymic);

    if(librarian_info.phone.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(QString("'%1'").arg(librarian_info.phone));

    if(librarian_info.email.isEmpty())
        str = str.arg("NULL");
    else str = str.arg(QString("'%1'").arg(librarian_info.email));


    QSqlQuery query;
    make_query(query, str);
}

void DAO::update_librarian(int librarian_id, const LibrarianInfo &librarian_info)
{
    QSqlQuery query;

    if(!librarian_info.login.isEmpty())
        make_query(query, QString("CALL set_login_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.login));
    if(!librarian_info.password.isEmpty())
        make_query(query, QString("CALL set_password_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.password));
    if(!librarian_info.name.isEmpty())
        make_query(query, QString("CALL set_name_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.name));
    if(!librarian_info.surname.isEmpty())
        make_query(query, QString("CALL set_surname_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.surname));
    if(!librarian_info.patronymic.isEmpty())
        make_query(query, QString("CALL set_patronymic_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.patronymic));
    if(!librarian_info.phone.isEmpty())
        make_query(query, QString("CALL set_phone_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.phone));
    if(!librarian_info.email.isEmpty())
        make_query(query, QString("CALL set_email_to_librarian(%1, '%2');").arg(librarian_id).arg(librarian_info.email));
}

void DAO::delete_librarian(int librarian_id)
{
    QSqlQuery query;
    make_query(query, QString("CALL delete_librarian_by_id(%1);").arg(librarian_id));
}

QSqlQueryModel &DAO::show_all_rooms()
{
    model->setQuery("CALL get_all_rooms()");
    if(model->lastError().isValid())
        throw std::runtime_error(model->lastError().text().toStdString());

    return *model;
}

void DAO::create_room(const RoomInfo &room_info)
{
    QString str_template("CALL create_room('%1');");
    QString str;

    if(room_info.name.isEmpty())
        throw std::runtime_error("Room name can't be empty.");
    str = str_template.arg(room_info.name);

    QSqlQuery query;
    make_query(query, str);
}

void DAO::update_room(int room_id, const RoomInfo &room_info)
{
    QString str_template("CALL set_name_to_room(%1, '%2');");
    QSqlQuery query;

    if(!room_info.name.isEmpty())
        make_query(query, str_template.arg(room_id).arg(room_info.name));
}

void DAO::delete_room(int room_id)
{
    QSqlQuery query;
    make_query(query, QString("CALL delete_room_by_id(%1);").arg(room_id));
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
