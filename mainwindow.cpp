#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>

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
    ADD_BOOK_PAGE = 8,
    FIND_BOOK_PAGE = 9,
    ENTER_READER_ID_PAGE = 10,
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

void MainWindow::on_add_book_btn_clicked()
{
    stackedWidget->setCurrentIndex(ADD_BOOK_PAGE);
}

void MainWindow::on_show_all_books_for_librarian_btn_2_clicked()
{
    QSqlQueryModel& model = dao.show_all_books_for_librarian();
    ui->work_with_books_for_librarian_table_view->setModel(&model);
}

void MainWindow::on_work_with_books_for_librarian_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
    ui->work_with_books_for_librarian_table_view->setModel(nullptr);
}

void MainWindow::on_add_book_btn_2_clicked()
{
    BookInfo book_info;
    book_info.book_name = ui->book_name_line_edit->text();
    book_info.author_name = ui->author_name_line_edit->text();
    book_info.author_surname = ui->author_surname_line_edit->text();
    book_info.author_patronymic = ui->author_patronymic_line_edit->text();
    book_info.author_pseudonym = ui->author_pseudonym_line_edit->text();
    book_info.publication_year = ui->publication_year_line_edit->text().toInt();
    book_info.publisher_name = ui->publisher_name_line_edit->text();
    book_info.isbn = ui->isbn_line_edit->text();
    book_info.amount = ui->book_amount_line_edit->text().toInt();

    // TODO: Сделать диалоговые окна, которые будут говорит, что происходит
    try
    {
        dao.add_book(book_info);
    }  catch (std::exception& ex)
    {
        qDebug() << ex.what() << '\n';
    }


    stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
}

void MainWindow::on_find_book_for_librarianbtn_clicked()
{
    stackedWidget->setCurrentIndex(FIND_BOOK_PAGE);
}

void MainWindow::on_find_book_btn_clicked()
{
    QString book_name = ui->book_name_in_find_book_page_line_edit->text();
    auto& model = dao.find_book_by_name(book_name);
    ui->work_with_books_for_librarian_table_view->setModel(&model);
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
}

void MainWindow::on_show_booked_book_of_reader_btn_clicked()
{
    stackedWidget->setCurrentIndex(ENTER_READER_ID_PAGE);
}

void MainWindow::on_enter_reader_id_btn_clicked()
{
    entered_reader_id = ui->enter_reader_id_line_edit->text().toInt();
    auto& model = dao.show_booked_book_by_reader_id(entered_reader_id);
    ui->work_with_booked_book_table_view->setModel(&model);
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKED_BOOK);
}

void MainWindow::on_lend_book_to_user_btn_clicked()
{
    auto* const view = ui->work_with_booked_book_table_view;
    const auto& model = view->model();

    int book_id = model->index(view->currentIndex().row(), 0).data().toInt();
    dao.lend_book(book_id, entered_reader_id);
    view->setModel(nullptr);
}

void MainWindow::on_pushButton_clicked()
{
    // DON'T DELETE.
}

void MainWindow::on_work_with_readers_for_librarian_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
    ui->work_with_readers_for_librarian_table_view->setModel(nullptr);
}

void MainWindow::on_work_with_debtors_for_librarian_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
    ui->work_with_debtors_for_librarian_table_view->setModel(nullptr);
}

void MainWindow::on_work_with_booked_book_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
    ui->work_with_booked_book_table_view->setModel(nullptr);
}
