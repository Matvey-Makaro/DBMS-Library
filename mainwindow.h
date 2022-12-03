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

private:
    Ui::MainWindow *ui;
    DAO& dao;

    Role role;

    QStackedWidget* stackedWidget;
};
#endif // MAINWINDOW_H
