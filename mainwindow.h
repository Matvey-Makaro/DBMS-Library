#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include "dao.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DAO& dao, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_authorize_as_admin_btn_clicked();

    void on_authorize_as_librarian_btn_clicked();

    void on_authorize_as_reader_btn_clicked();

    void on_enter_authorize_btn_clicked();

    void on_work_with_books_for_librarian_btn_clicked();

    void on_works_with_readers_for_librarian_btn_clicked();

    void on_work_with_debtors_for_librarian_btn_clicked();

    void on_work_with_booked_book_for_librarian_btn_clicked();

    void on_add_book_btn_clicked();

    void on_show_all_books_for_librarian_btn_2_clicked();

    void on_work_with_books_for_librarian_back_btn_clicked();

    void on_add_book_btn_2_clicked();

    void on_find_book_for_librarianbtn_clicked();

    void on_find_book_btn_clicked();

    void on_show_booked_book_of_reader_btn_clicked();

    void on_enter_reader_id_btn_clicked();

    void on_lend_book_to_user_btn_clicked();

    void on_pushButton_clicked();

    void on_work_with_readers_for_librarian_back_btn_clicked();

    void on_work_with_debtors_for_librarian_back_btn_clicked();

    void on_work_with_booked_book_back_btn_clicked();

    void on_enter_for_authorization_reader_btn_clicked();

    void on_show_all_books_for_reader_btn_clicked();

    void on_work_with_books_for_reader_btn_clicked();

    void on_work_with_booked_books_for_reader_btn_clicked();

    void on_information_about_reader_btn_clicked();

    void on_information_about_reader_back_btn_clicked();

    void on_work_with_booked_book_for_readers_back_btn_clicked();

    void on_work_with_books_for_readers_back_btn_clicked();

    void on_find_books_for_reader_clicked();

    void on_book_book_for_reader_btn_clicked();

    void on_show_booked_book_for_reader_btn_clicked();

    void on_cancle_booking_book_for_reader_btn_clicked();

    void on_show_debts_for_reader_btn_clicked();

    void on_show_taken_books_for_reader_btn_clicked();

    void on_add_book_back_btn_clicked();

    void on_show_all_librarians_for_admin_btn_clicked();

    void on_work_with_librarians_btn_clicked();

    void on_work_with_rooms_btn_clicked();

    void on_add_librarian_for_admin_btn_clicked();

    void on_add_librarian_on_add_librarian_page_btn_clicked();

    void on_add_librarian_back_btn_clicked();

    void on_update_librarian_for_admin_btn_clicked();

    void on_delete_librarian_for_admin_btn_clicked();

    void on_work_with_librarians_back_btn_clicked();

    void on_show_rooms_on_work_with_rooms_page_btn_clicked();

    void on_add_room_on_work_with_rooms_page_btn_clicked();

    void on_update_room_on_work_with_rooms_page_btn_clicked();

    void on_fill_room_information_page_back_btn_clicked();

    void on_add_room_on_fill_room_info_page_btn_clicked();

    void on_delete_room_on_work_with_rooms_page_btn_clicked();

    void on_work_with_rooms_page_back_btn_clicked();

    void on_update_book_btn_clicked();

    void on_delete_book_btn_clicked();

    void on_add_reader_for_librarian_btn_clicked();

    void on_add_reader_page_back_btn_clicked();

    void on_add_for_add_reader_page_btn_clicked();

    void on_show_all_readers_for_librarian_btn_clicked();

    void on_update_reader_for_librarian_btn_clicked();

    void on_add_or_update_for_add_reader_page_btn_clicked();

    void on_delete_reader_for_librarian_btn_clicked();

    void on_show_taken_book_of_reader_for_librarian_btn_clicked();

    void on_get_book_from_reader_for_librarian_btn_clicked();

    void on_pushButton_25_clicked();

    void on_show_all_debtors_for_librarian_btn_clicked();

    void on_show_readers_debts_btn_clicked();

private:
    void set_max_lengths();

private:
    Ui::MainWindow *ui;
    DAO& dao;

    Role role;

    QStackedWidget* stackedWidget;

    int entered_reader_id;
    int current_librarian_id;
    int current_room_id;
    int current_book_id;
    int current_reader_id;
    bool is_creation_now;
    bool is_get_book_from_reader_for_librarian_btn_enable;
    bool is_reader_on_table_view;

private:
    static const int login_size = 45;
    static const int password_size = 32;
    static const int name_size = 45;
    static const int phone_size = 13;
    static const int email_size = 45;
    static const int isbn_size = 45;
    static const int literary_work_name = 200;
    static const int int_size = 11;
    static const int passport_series_size = 5;
    static const int passport_number_size = 20;
    static const int address_size = 100;
    static const int year_size = 4;
};
#endif // MAINWINDOW_H
