#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

enum Pages
{
    AUTHORIZATION_AS = 0,
    AUTHORIZATION = 1,
    AUTHORIZATION_FOR_READER = 2,
    START_LIBRARIAN_PAGE = 3,
    WORK_WITH_BOOKS_FOR_LIBRARIAN = 4,
    WORK_WITH_READERS_FOR_LIBRARIAN = 5,
    WORK_WITH_DEBTORS_FOR_LIBRARIAN = 6,
    WORK_WITH_BOOKED_BOOK = 7,
};

MainWindow::MainWindow(DAO& dao, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dao(dao)
{
    ui->setupUi(this);
    stackedWidget = ui->stackedWidget;
    stackedWidget->setCurrentIndex(AUTHORIZATION_AS);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_authorize_as_admin_btn_clicked()
{
    role = Role::ADMIN;
    stackedWidget->setCurrentIndex(AUTHORIZATION);
}

void MainWindow::on_authorize_as_librarian_btn_clicked()
{
    role = Role::LIBRARIAN;
    stackedWidget->setCurrentIndex(AUTHORIZATION);
}

void MainWindow::on_authorize_as_reader_btn_clicked()
{
    role = Role::READER;
}

void MainWindow::on_enter_authorize_btn_clicked()
{
    QString login = ui->login_line_edit->text();
    QString password = ui->password_line_edit->text();

    if(!dao.authorize(role, login, password))
    {
        // TODO: Выдать окно, что неправильно введён логин или пароль.
        ui->password_line_edit->setText("");
        return;
    }

    stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);

}

void MainWindow::on_work_with_books_for_librarian_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
}

void MainWindow::on_works_with_readers_for_librarian_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_READERS_FOR_LIBRARIAN);
}

void MainWindow::on_work_with_debtors_for_librarian_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_DEBTORS_FOR_LIBRARIAN);
}

void MainWindow::on_work_with_booked_book_for_librarian_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKED_BOOK);
}
