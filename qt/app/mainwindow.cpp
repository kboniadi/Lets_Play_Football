#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	DBManager::instance();

    ui->pushButton_pages_home->setDisabled(true);

}

MainWindow::~MainWindow()
{
	delete ui;
}

