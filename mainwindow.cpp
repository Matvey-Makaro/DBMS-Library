#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>
#include <QMessageBox>

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
    START_READER_PAGE = 11,
    WORK_WITH_BOOKS_FOR_READERS = 12,
    WORK_WITH_BOOKED_BOOK_FOR_READER = 13,
    INFORMATION_ABOUT_READER = 14,
    START_ADMIN_PAGE = 15,
    WORK_WITH_LIBRARIANS_PAGE = 16,
    WORK_WITH_ROOMS_PAGE = 17,
    ADD_LIBRARIAN_PAGE = 18,
    FILL_ROOM_INFORMATION_PAGE = 19,
    ADD_READER_PAGE = 20,
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
    stackedWidget->setCurrentIndex(AUTHORIZATION_FOR_READER);
}

void MainWindow::on_enter_authorize_btn_clicked()
{
    try
    {
        QString login = ui->login_line_edit->text();
        QString password = ui->password_line_edit->text();

        if(!dao.authorize(role, login, password))
        {
            QMessageBox::warning(this, "Warning", "Неверный логин или пароль.");
            ui->password_line_edit->setText("");
            return;
        }

        if(role == Role::LIBRARIAN)
            stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
        else if(role == Role::ADMIN)
            stackedWidget->setCurrentIndex(START_ADMIN_PAGE);
        else assert(0);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }

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
    ui->main_add_book_label->setText("Заполните данные книги:");
    ui->add_book_btn_2->setText("Добавить");
    is_creation_now = false;

    ui->work_with_books_for_librarian_table_view->setModel(nullptr);
    stackedWidget->setCurrentIndex(ADD_BOOK_PAGE);
}

void MainWindow::on_show_all_books_for_librarian_btn_2_clicked()
{
    try
    {
        QSqlQueryModel& model = dao.show_all_books_for_librarian();
        ui->work_with_books_for_librarian_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_work_with_books_for_librarian_back_btn_clicked()
{
    try
    {
        stackedWidget->setCurrentIndex(START_LIBRARIAN_PAGE);
        ui->work_with_books_for_librarian_table_view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_book_btn_2_clicked()
{
    try
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

        dao.add_book(book_info);
        stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_find_book_for_librarianbtn_clicked()
{
    stackedWidget->setCurrentIndex(FIND_BOOK_PAGE);
}

void MainWindow::on_find_book_btn_clicked()
{
    try
    {
        QString book_name = ui->book_name_in_find_book_page_line_edit->text();
        auto& model = dao.find_book_by_name(book_name);
        if(role == Role::LIBRARIAN)
        {
            ui->work_with_books_for_librarian_table_view->setModel(&model);
            stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
        }
        else if(role == Role::READER)
        {
            ui->work_with_books_for_readers_table_view->setModel(&model);
            stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_READERS);
        }
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_booked_book_of_reader_btn_clicked()
{
    stackedWidget->setCurrentIndex(ENTER_READER_ID_PAGE);
}

void MainWindow::on_enter_reader_id_btn_clicked()
{
    try
    {
        entered_reader_id = ui->enter_reader_id_line_edit->text().toInt();
        auto& model = dao.show_booked_book_by_reader_id(entered_reader_id);
        ui->work_with_booked_book_table_view->setModel(&model);
        stackedWidget->setCurrentIndex(WORK_WITH_BOOKED_BOOK);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }

}

void MainWindow::on_lend_book_to_user_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_booked_book_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        int book_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.lend_book(book_id, entered_reader_id);
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
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

void MainWindow::on_enter_for_authorization_reader_btn_clicked()
{
    try
    {
        QString name = ui->name_for_authorization_reader_line_edit->text();
        QString surname = ui->surname_for_authorization_for_reader_line_edit->text();
        QString number = ui->passport_number_for_authorization_reader_line_edit->text();

        if(!dao.authorize_reader(name, surname, number))
        {
            QMessageBox::warning(this, "Warning", "Такого читателя не существует.");
            ui->password_line_edit->setText("");
            return;
        }

        stackedWidget->setCurrentIndex(START_READER_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_all_books_for_reader_btn_clicked()
{
    try
    {
        QSqlQueryModel& model = dao.show_all_books_for_reader();
        ui->work_with_books_for_readers_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_work_with_books_for_reader_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_READERS);
}

void MainWindow::on_work_with_booked_books_for_reader_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKED_BOOK_FOR_READER);
}

void MainWindow::on_information_about_reader_btn_clicked()
{
    stackedWidget->setCurrentIndex(INFORMATION_ABOUT_READER);
}

void MainWindow::on_information_about_reader_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_READER_PAGE);
    ui->information_about_reader_table_view->setModel(nullptr);
}

void MainWindow::on_work_with_booked_book_for_readers_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_READER_PAGE);
    ui->work_with_booked_book_for_readers_table_view->setModel(nullptr);
}

void MainWindow::on_work_with_books_for_readers_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(START_READER_PAGE);
    ui->work_with_books_for_readers_table_view->setModel(nullptr);
}

void MainWindow::on_find_books_for_reader_clicked()
{
    stackedWidget->setCurrentIndex(FIND_BOOK_PAGE);
}

void MainWindow::on_book_book_for_reader_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_books_for_readers_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        int book_id = model->index(view->currentIndex().row(), 0).data().toInt();
        qDebug() << book_id << '\n';
        dao.book_book(book_id);
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_booked_book_for_reader_btn_clicked()
{
    try
    {
        auto& model = dao.show_booked_book();
        ui->work_with_booked_book_for_readers_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_cancle_booking_book_for_reader_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_booked_book_for_readers_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        int book_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.cancle_booking(book_id);
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_debts_for_reader_btn_clicked()
{
    try
    {
        auto& model = dao.show_debtor_books();
        ui->information_about_reader_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_taken_books_for_reader_btn_clicked()
{
    try
    {
        auto& model = dao.show_taken_books();
        ui->information_about_reader_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_book_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_BOOKS_FOR_LIBRARIAN);
}

void MainWindow::on_work_with_librarians_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_LIBRARIANS_PAGE);
}

void MainWindow::on_work_with_rooms_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_ROOMS_PAGE);
}

void MainWindow::on_show_all_librarians_for_admin_btn_clicked()
{
    try
    {
        auto& model = dao.show_all_librarians();
        ui->work_with_librarians_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}



void MainWindow::on_add_librarian_for_admin_btn_clicked()
{
    ui->top_add_librarian_page_label->setText("Заполните данные библиотекаря:");
    ui->add_librarian_on_add_librarian_page_btn->setText("Добавить");
    is_creation_now = true;

    ui->work_with_librarians_table_view->setModel(nullptr);
    stackedWidget->setCurrentIndex(ADD_LIBRARIAN_PAGE);
}

void MainWindow::on_add_librarian_on_add_librarian_page_btn_clicked()
{
    try
    {
        LibrarianInfo librarian_info;
        librarian_info.login = ui->login_for_librarian_line_edit->text();
        librarian_info.password = ui->password_for_librarian_line_edit->text();
        librarian_info.name = ui->name_for_librarian_line_edit->text();
        librarian_info.surname = ui->surname_for_librarian_line_edit->text();
        librarian_info.patronymic = ui->patronymic_for_librarian_line_edit->text();
        librarian_info.phone = ui->phone_for_librarian_line_edit->text();
        librarian_info.email = ui->email_for_librarian_line_edit->text();

        if(is_creation_now)
            dao.create_librarian(librarian_info);
        else dao.update_librarian(current_librarian_id, librarian_info);

        stackedWidget->setCurrentIndex(WORK_WITH_LIBRARIANS_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_librarian_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_LIBRARIANS_PAGE);
}

void MainWindow::on_update_librarian_for_admin_btn_clicked()
{
    try
    {
        ui->top_add_librarian_page_label->setText("Измените данные библиотекаря:");
        ui->add_librarian_on_add_librarian_page_btn->setText("Изменить");
        is_creation_now = false;

        auto* const view = ui->work_with_librarians_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_librarian_id = model->index(view->currentIndex().row(), 0).data().toInt();
        view->setModel(nullptr);

        stackedWidget->setCurrentIndex(ADD_LIBRARIAN_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_delete_librarian_for_admin_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_librarians_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_librarian_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.delete_librarian(current_librarian_id);
        current_librarian_id = 0;
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_work_with_librarians_back_btn_clicked()
{
    ui->work_with_librarians_table_view->setModel(nullptr);
    stackedWidget->setCurrentIndex(START_ADMIN_PAGE);
}

void MainWindow::on_show_rooms_on_work_with_rooms_page_btn_clicked()
{
    try
    {
        auto& model = dao.show_all_rooms();
        ui->work_with_rooms_page_table_view->setModel(&model);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_room_on_work_with_rooms_page_btn_clicked()
{
    try
    {
        ui->add_room_on_fill_room_info_page_btn->setText("Добавить");
        is_creation_now = true;

        ui->work_with_rooms_page_table_view->setModel(nullptr);
        stackedWidget->setCurrentIndex(FILL_ROOM_INFORMATION_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_update_room_on_work_with_rooms_page_btn_clicked()
{
    try
    {
        ui->add_room_on_fill_room_info_page_btn->setText("Изменить");
        is_creation_now = false;

        auto* const view = ui->work_with_rooms_page_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_room_id = model->index(view->currentIndex().row(), 0).data().toInt();
        view->setModel(nullptr);

        stackedWidget->setCurrentIndex(FILL_ROOM_INFORMATION_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_fill_room_information_page_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_ROOMS_PAGE);
}

void MainWindow::on_add_room_on_fill_room_info_page_btn_clicked()
{
    try
    {
        RoomInfo room_info;
        room_info.name = ui->room_name_line_edti->text();

        if(is_creation_now)
            dao.create_room(room_info);
        else dao.update_room(current_room_id, room_info);

        stackedWidget->setCurrentIndex(WORK_WITH_ROOMS_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_delete_room_on_work_with_rooms_page_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_rooms_page_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_room_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.delete_room(current_room_id);
        current_room_id = 0;
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_work_with_rooms_page_back_btn_clicked()
{
    ui->work_with_rooms_page_table_view->setModel(nullptr);
    stackedWidget->setCurrentIndex(START_ADMIN_PAGE);
}

void MainWindow::on_update_book_btn_clicked()
{
//    try
//    {
//        ui->main_add_book_label->setText("Измените данные книги");
//        ui->add_book_btn_2->setText("Изменить");
//        is_creation_now = false;

//        auto* const view = ui->work_with_books_for_librarian_table_view;
//        const auto* model = view->model();
//        if(model == nullptr)
//            return;

//        current_room_id = model->index(view->currentIndex().row(), 0).data().toInt();
//        view->setModel(nullptr);

//        stackedWidget->setCurrentIndex(FILL_ROOM_INFORMATION_PAGE);
//    }
//    catch (std::exception& ex)
//    {
//        QMessageBox::warning(this, "Error", ex.what());
//        qDebug() << ex.what() << '\n';
//    }
}

void MainWindow::on_delete_book_btn_clicked()
{
    try
    {
        auto* const view = ui->work_with_books_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_book_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.delete_book(current_book_id);
        current_book_id = 0;
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_reader_for_librarian_btn_clicked()
{
    try
    {
        ui->add_or_update_for_add_reader_page_btn->setText("Добавить");
        is_creation_now = true;

        ui->work_with_rooms_page_table_view->setModel(nullptr);
        is_get_book_from_reader_for_librarian_btn_enable = false;
        stackedWidget->setCurrentIndex(ADD_READER_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_reader_page_back_btn_clicked()
{
    stackedWidget->setCurrentIndex(WORK_WITH_READERS_FOR_LIBRARIAN);
}

void MainWindow::on_add_for_add_reader_page_btn_clicked()
{
    // DON'T DELETE.
}

void MainWindow::on_show_all_readers_for_librarian_btn_clicked()
{
    try
    {
        auto& model = dao.show_all_readers();
        ui->work_with_readers_for_librarian_table_view->setModel(&model);
        is_get_book_from_reader_for_librarian_btn_enable = false;
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_update_reader_for_librarian_btn_clicked()
{
    try
    {
        if(is_get_book_from_reader_for_librarian_btn_enable)
            return;

        ui->add_or_update_for_add_reader_page_btn->setText("Изменить");
        is_creation_now = false;

        auto* const view = ui->work_with_readers_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_reader_id = model->index(view->currentIndex().row(), 0).data().toInt();
        view->setModel(nullptr);
        is_get_book_from_reader_for_librarian_btn_enable = false;

        stackedWidget->setCurrentIndex(ADD_READER_PAGE);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_add_or_update_for_add_reader_page_btn_clicked()
{
    try
    {
        ReaderInfo reader_info;
        reader_info.name = ui->name_for_add_reader_line_edit->text();
        reader_info.surname = ui->surname_for_add_reader_line_edit->text();
        reader_info.patronymic = ui->patronymic_for_add_reader_line_edit->text();
        reader_info.phone = ui->phone_for_add_reader_line_edit->text();
        reader_info.email = ui->email_for_add_reader_line_edit->text();
        reader_info.address = ui->address_for_add_reader_line_edit->text();
        reader_info.passport_series = ui->passport_series_for_add_reader_line_edit->text();
        reader_info.passport_number = ui->passport_number_for_add_reader_line_edit->text();

        if(!reader_info.passport_number.isEmpty() && reader_info.passport_series.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Passport series cannot be empty if the passport number is not empty.");
            return;
        }

        else if(reader_info.passport_number.isEmpty() && !reader_info.passport_series.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Passport number cannot be empty if the passport series is not empty.");
            return;
        }

        if(is_creation_now)
            dao.create_reader(reader_info);
        else dao.update_reader(current_reader_id, reader_info);

        is_get_book_from_reader_for_librarian_btn_enable = false;
        stackedWidget->setCurrentIndex(WORK_WITH_READERS_FOR_LIBRARIAN);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_delete_reader_for_librarian_btn_clicked()
{
    try
    {
        if(is_get_book_from_reader_for_librarian_btn_enable)
            return;

        auto* const view = ui->work_with_readers_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_reader_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.delete_reader(current_reader_id);
        current_reader_id = 0;
        view->setModel(nullptr);
        is_get_book_from_reader_for_librarian_btn_enable = false;
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_taken_book_of_reader_for_librarian_btn_clicked()
{
    try
    {
        if(is_get_book_from_reader_for_librarian_btn_enable)
            return;

        auto* const view = ui->work_with_readers_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_reader_id = model->index(view->currentIndex().row(), 0).data().toInt();

        auto& new_model = dao.show_taken_books(current_reader_id);
        ui->work_with_readers_for_librarian_table_view->setModel(&new_model);
        is_get_book_from_reader_for_librarian_btn_enable = true;
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_get_book_from_reader_for_librarian_btn_clicked()
{
    try
    {
        if(!is_get_book_from_reader_for_librarian_btn_enable)
            return;

        auto* const view = ui->work_with_readers_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_book_id = model->index(view->currentIndex().row(), 0).data().toInt();
        dao.accept_book_from_reader(current_book_id, current_reader_id);
        view->setModel(nullptr);
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    // DON'T DELETE
}

void MainWindow::on_show_all_debtors_for_librarian_btn_clicked()
{
    try
    {
        auto& model = dao.show_all_debtors();
        ui->work_with_debtors_for_librarian_table_view->setModel(&model);
        is_reader_on_table_view = true;
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }
}

void MainWindow::on_show_readers_debts_btn_clicked()
{
    try
    {
        if(!is_reader_on_table_view)
            return;

        auto* const view = ui->work_with_debtors_for_librarian_table_view;
        const auto* model = view->model();
        if(model == nullptr)
            return;

        current_reader_id = model->index(view->currentIndex().row(), 0).data().toInt();
        auto& new_model = dao.show_debtor_books(current_reader_id);
        view->setModel(&new_model);
        is_reader_on_table_view = false;
    }
    catch (std::exception& ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
        qDebug() << ex.what() << '\n';
    }


}
