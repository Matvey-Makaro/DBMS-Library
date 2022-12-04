#ifndef MODELS_H
#define MODELS_H

#include <QString>

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

struct LibrarianInfo
{
    QString login;
    QString password;
    QString name;
    QString surname;
    QString patronymic;
    QString phone;
    QString email;
};

struct RoomInfo
{
    QString name;
};

#endif // MODELS_H
