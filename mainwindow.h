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

private:
    Ui::MainWindow *ui;
    DAO& dao;

    Role role;

    QStackedWidget* stackedWidget;

    int entered_reader_id;
};
#endif // MAINWINDOW_H
