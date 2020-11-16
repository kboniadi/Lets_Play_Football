#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QSqlQueryModel>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	DBManager::instance();

    initializeLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::populateStadiumInfo(int sortIndex, int filterIndex)
{

    QSqlQuery query;
    QString queryString = "SELECT stadiumName,seatCap,conference,division,surfaceType,roofType,dateOpen FROM information";
    if (filterIndex == OpenRoof)
        queryString += " WHERE roofType = 'Open'";

    switch(sortIndex)
    {
    case StadiumName: queryString += " ORDER BY stadiumName ASC";
                      break;
    case Capacity: queryString += " ORDER BY seatCap ASC";
                   break;
    case DateOpened: queryString += " ORDER BY dateOpen ASC";
                    break;
    }

    query.exec(queryString);

    int capacity = 0;
    int openRoofCount = 0;

    QLocale c(QLocale::C);  // to set the string with "," (ex: 12,500) into int
    while(query.next())
    {

        capacity += c.toInt(query.value(1).toString());
        if (query.value(5).toString() == "Open")
            openRoofCount++;
    }
    ui->label_list_totalroofs->setText("Total Open Roof Stadiums: " + QString::number(openRoofCount));
    ui->label_list_totalcapacity->setText("Total Capacity: " + QString("%L1").arg(capacity));

    ui->label_list_totalroofs->show();
    ui->label_list_totalcapacity->show();

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Stadium Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Seat Cap"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Conference"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Division"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Surface Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Roof Type"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Open"));

    ui->tableView_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_list->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_list->setModel(model);



}

/*----NAVIGATION----*/
void MainWindow::on_pushButton_pages_home_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(HOME);
    clearButtons();
    ui->pushButton_pages_home->setDisabled(true);
}

void MainWindow::on_pushButton_pages_view_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(VIEW);
    clearButtons();
    on_pushButton_view_search_clicked();
    ui->pushButton_pages_view->setDisabled(true);
}
    void MainWindow::on_pushButton_view_search_clicked()
    {
        ui->stackedWidget_view_pages->setCurrentIndex(SEARCH);
        ui->pushButton_view_search->setDisabled(true);
        ui->pushButton_view_list->setDisabled(false);
        populateSouvenirs("");
        populateTeams();
    }

    void MainWindow::on_pushButton_view_list_clicked()
    {
        clearButtons();
        ui->stackedWidget_view_pages->setCurrentIndex(LIST);
        ui->pushButton_view_search->setDisabled(false);
        ui->pushButton_view_list->setDisabled(true);
        ui->comboBox_list_type->setCurrentIndex(0);
        on_comboBox_list_type_activated(0);
    }

    void MainWindow::on_comboBox_list_type_activated(int index)
    {
        clearButtons();
        if (index == 0)
        {
            ui->comboBox_list_sort->addItems(sortTeams);
            ui->comboBox_list_filter->addItems(filterTeams);
        }
        else
        {
            ui->comboBox_list_sort->addItems(sortStadiums);
            ui->comboBox_list_filter->addItems(filterStadiums);
        }

    }

void MainWindow::on_pushButton_pages_plan_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PLAN);
    clearButtons();
    ui->pushButton_pages_plan->setDisabled(true);
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
    clearButtons();
    on_pushButton_admin_import_clicked();
    ui->pushButton_pages_admin->setDisabled(true);
}

    void MainWindow::on_pushButton_login_clicked()
    {
        ui->stackedWidget_pages->setCurrentIndex(ADMIN);
    }

    void MainWindow::on_pushButton_admin_import_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(IMPORT);
        ui->pushButton_admin_import->setDisabled(true);
        ui->pushButton_admin_edit->setDisabled(false);
    }

    void MainWindow::on_pushButton_admin_edit_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(EDIT);
        ui->pushButton_admin_import->setDisabled(false);
        ui->pushButton_admin_edit->setDisabled(true);
    }

    void MainWindow::on_comboBox_edit_activated(int index)
    {
        clearButtons();
        if (index == 0)
        {
            ui->formWidget_edit_souvenir->setVisible(true);
            ui->formWidget_edit_stadium->setVisible(false);
        }
        else
        {
            ui->formWidget_edit_souvenir->setVisible(false);
            ui->formWidget_edit_stadium->setVisible(true);
        }
    }
/*----END NAVIGATION----*/

/*----HELPER FUNCTIONS----*/
void MainWindow::initializeLayout() // sets default pages on program restart
{
    on_pushButton_pages_home_clicked();
    on_comboBox_edit_activated(0);
    ui->pushButton_pages_home->setDisabled(true);
}
void MainWindow::clearButtons() // resets most program states
{
    // home pages
    ui->pushButton_pages_home->setDisabled(false);
    ui->pushButton_pages_view->setDisabled(false);
    ui->pushButton_pages_plan->setDisabled(false);
    ui->pushButton_pages_admin->setDisabled(false);

    // view combo boxes
    ui->comboBox_list_sort->clear();
    ui->comboBox_list_filter->clear();

    // trip planning buttons
    ui->pushButton_plan_sort->setVisible(false);
    ui->gridWidget_plan_custom->setVisible(false);
    ui->tableView_plan_custom->setVisible(false);
    ui->pushButton_plan_continue->setDisabled(true);
    ui->pushButton_plan_packers->setDisabled(false);
    ui->pushButton_plan_patriots->setDisabled(false);
    ui->pushButton_plan_rams->setDisabled(false);
    ui->pushButton_plan_vikings->setDisabled(false);
    ui->pushButton_plan_custom->setDisabled(false);
    ui->pushButton_plan_MST->setDisabled(false);


    // admin buttons
    ui->formWidget_edit_souvenir->setDisabled(true);
    ui->formWidget_edit_stadium->setDisabled(true);
    ui->pushButton_edit_confirm->setDisabled(true);
    ui->pushButton_edit_cancel->setDisabled(true);
    ui->pushButton_edit_edit->setDisabled(true);
    ui->pushButton_edit_delete->setDisabled(true);
    ui->pushButton_edit_add->setDisabled(false);

    // line edits
    ui->lineEdit_edit_souvenir_name->clear();
    ui->lineEdit_edit_souvenir_price->clear();
    ui->lineEdit_edit_souvenir_team->clear();
    ui->lineEdit_login_password->clear();
    ui->lineEdit_login_username->clear();
    ui->LineEdit_edit_stadium_capacity->clear();
    ui->LineEdit_edit_stadium_location->clear();
    ui->LineEdit_edit_stadium_name->clear();
    ui->LineEdit_edit_stadium_roof->clear();
    ui->LineEdit_edit_stadium_surface->clear();

    // labels
    ui->label_list_totalroofs->clear();
    ui->label_list_totalcapacity->clear();
}

void MainWindow::on_pushButton_edit_add_clicked() // admin add button
{
    ui->formWidget_edit_souvenir->setDisabled(false);
    ui->formWidget_edit_stadium->setDisabled(false);
    ui->pushButton_edit_add->setDisabled(true);
    ui->pushButton_edit_cancel->setDisabled(false);

    // code + error checking

    ui->pushButton_edit_confirm->setDisabled(false);

}

void MainWindow::on_pushButton_edit_confirm_clicked()
{
    clearButtons();
}

void MainWindow::on_pushButton_edit_cancel_clicked()
{
    clearButtons();
}

void MainWindow::on_pushButton_plan_packers_clicked()
{
    clearButtons();
    ui->pushButton_plan_packers->setDisabled(true);
    ui->gridWidget_plan_custom->setVisible(true);
    ui->tableView_plan_custom->setVisible(true);
    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_patriots_clicked()
{
    clearButtons();
    ui->pushButton_plan_patriots->setDisabled(true);

    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_rams_clicked()
{
    clearButtons();
    ui->pushButton_plan_rams->setDisabled(true);

    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_vikings_clicked()
{
    clearButtons();
    ui->pushButton_plan_vikings->setDisabled(true);

    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_custom_clicked()
{
    clearButtons();
    ui->pushButton_plan_sort->setVisible(true);
    ui->gridWidget_plan_custom->setVisible(true);
    ui->tableView_plan_custom->setVisible(true);
    ui->pushButton_plan_custom->setDisabled(true);

    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_MST_clicked()
{
    clearButtons();
    ui->pushButton_plan_MST->setDisabled(true);
}

/*----END HELPER FUNCTIONS----*/


void MainWindow::on_comboBox_list_type_currentIndexChanged(int index)
{
    clearButtons();

    QSqlQueryModel* model = new QSqlQueryModel;
    ui->tableView_list->setModel(model);
    if (index == 1) // case stadium view
        populateStadiumInfo(StadiumName,All);
    //if (index == 0)   // case team view
}


void MainWindow::on_comboBox_list_sort_currentIndexChanged(int index)
{
    if (ui->comboBox_list_type->currentIndex() == 1)
        populateStadiumInfo(index, ui->comboBox_list_filter->currentIndex());
}




void MainWindow::on_comboBox_list_filter_currentIndexChanged(int index)
{
    if (ui->comboBox_list_type->currentIndex() == 1)
        populateStadiumInfo(ui->comboBox_list_sort->currentIndex(), index);
}

void MainWindow::populateTeams()
{
    QStringList teamList;
    DBManager::instance()->getTeams(teamList);

    QStringListModel* model = new QStringListModel;
    model->setStringList(teamList);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Teams"));

    ui->tableView_search_teams->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_search_teams->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_search_teams->setModel(model);
    ui->tableView_search_teams->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_tableView_search_teams_doubleClicked(const QModelIndex &index)
{
    populateSouvenirs(index.data().toString());
}

void MainWindow::populateSouvenirs(QString team)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT items, price FROM souvenir WHERE id = (SELECT teams.id FROM teams WHERE teams.teamNames = '" + team + "')");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Souvenir"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Price"));

    ui->tableView_search_souvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_search_souvenirs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_search_souvenirs->setModel(model);
}
