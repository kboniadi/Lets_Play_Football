#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	DBManager::instance();
}

MainWindow::~MainWindow()
{
	delete ui;
}

/*----NAVIGATION----*/
void MainWindow::on_pushButton_pages_home_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
}

void MainWindow::on_pushButton_pages_view_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(VIEW);
}
    void MainWindow::on_pushButton_view_search_clicked()
    {
        ui->stackedWidget_view_pages->setCurrentIndex(SEARCH);
    }

    void MainWindow::on_pushButton_view_list_clicked()
    {
        ui->stackedWidget_view_pages->setCurrentIndex(LIST);
    }

void MainWindow::on_pushButton_pages_plan_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PLAN);
}

    void MainWindow::on_pushButton_plan_continue_clicked()
    {
        ui->stackedWidget_pages->setCurrentIndex(POS);
    }

    void MainWindow::on_pushButton_pos_cancel_clicked()
    {
        on_pushButton_pages_home_clicked();
    }

    void MainWindow::on_pushButton_pos_continue_clicked()
    {
        ui->stackedWidget_pages->setCurrentIndex(RECEIPT);
    }

    void MainWindow::on_pushButton_receipt_continue_clicked()
    {
        on_pushButton_pages_home_clicked();
    }

void MainWindow::on_pushButton_pages_admin_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(LOGIN);
}

    void MainWindow::on_pushButton_login_clicked()
    {
        ui->stackedWidget_pages->setCurrentIndex(ADMIN);
    }

    void MainWindow::on_pushButton_admin_import_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(IMPORT);
    }

    void MainWindow::on_pushButton_admin_edit_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(EDIT);
    }
/*----END NAVIGATION----*/



