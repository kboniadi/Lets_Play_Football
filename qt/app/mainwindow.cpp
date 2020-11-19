#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "tablemanager.h"
#include "layout.h"
#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	DBManager::instance();
	table = new TableManager;
    Layout::instance();

    initializeLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->stackedWidget_view_pages->setCurrentIndex(LIST);
        ui->pushButton_view_search->setDisabled(false);
        ui->pushButton_view_list->setDisabled(true);

        populateStadiumInfo(0,0,0);
    }

void MainWindow::on_pushButton_pages_plan_clicked()
{
    ui->stackedWidget_pages->setCurrentIndex(PLAN);
    clearButtons();
    ui->pushButton_pages_plan->setDisabled(true);
    on_pushButton_plan_MST_clicked();
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
	connect(ui->lineEdit_login_password, SIGNAL(returnPressed()), ui->pushButton_login, SLOT(click()));
}

    void MainWindow::on_pushButton_login_clicked()
    {
        // Check login credentials
        if(DBManager::instance()->checkLogin(ui->lineEdit_login_username->text(), ui->lineEdit_login_password->text()))
        {
            // Change index to admin section
            ui->stackedWidget_pages->setCurrentIndex(ADMIN);
			table->AdminInfoTable(ui->tableView_import);
			table->AdminDistTable(ui->tableView_import_2);
			table->AdminSouvTable(ui->tableView_import_3);
        }
        else
        {
            // Notify user if username and password are incorrect
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Username and/or password is incorrect."));
        }

        // Clear username and password fields
        ui->lineEdit_login_username->clear();
        ui->lineEdit_login_password->clear();
    }

    void MainWindow::on_pushButton_admin_import_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(IMPORT);
        ui->pushButton_admin_import->setDisabled(true);
        ui->pushButton_admin_edit->setDisabled(false);
    }

		void MainWindow::on_pushButton_import_clicked()
		{
			DBManager::instance()->ImportTeams();
			table->AdminInfoTable(ui->tableView_import);
			table->AdminDistTable(ui->tableView_import_2);
			table->AdminSouvTable(ui->tableView_import_3);
		}

    void MainWindow::on_pushButton_admin_edit_clicked()
    {
        ui->stackedWidget_admin_pages->setCurrentIndex(EDIT);
		ui->stackedWidget_edit->setCurrentIndex(EDITSOUV);
        ui->pushButton_admin_import->setDisabled(false);
        ui->pushButton_admin_edit->setDisabled(true);
		table->InitializeAdminEditTable(ui->tableWidget_edit);
		table->PopulateAdminEditTable(ui->tableWidget_edit);
    }

    void MainWindow::on_comboBox_edit_activated(int index)
    {
        clearButtons();

        if (index == 0)
        {
			ui->stackedWidget_edit->setCurrentIndex(EDITSOUV);
            ui->formWidget_edit_souvenir->setVisible(true);
			ui->formWidget_edit_stadium->setVisible(false);
			table->InitializeAdminEditTable(ui->tableWidget_edit);
			table->PopulateAdminEditTable(ui->tableWidget_edit);
        }
        else
        {
			ui->stackedWidget_edit->setCurrentIndex(EDITSTAD);
            ui->formWidget_edit_souvenir->setVisible(false);
            ui->formWidget_edit_stadium->setVisible(true);
			ui->tableView_edit->verticalHeader()->hide();
			table->AdminInfoTable(ui->tableView_edit);
        }
    }

    void MainWindow::on_pushButton_pages_exit_clicked()
    {
        QApplication::quit();
    }
/*----END NAVIGATION----*/

/*----HELPER FUNCTIONS----*/
void MainWindow::initializeLayout() // sets default pages on program restart
{
    on_pushButton_pages_home_clicked();
    on_comboBox_edit_activated(0);
    ui->pushButton_pages_home->setDisabled(true);
    ui->comboBox_list_sort->addItems(sort); // directory page
    ui->comboBox_list_filterteams->addItems(filterTeams);
    ui->comboBox_list_filterstadiums->addItems(filterStadiums);
    setResources();
}

void MainWindow::setResources() // imports and assigns layout elements
{
    /*----Fonts----*/
    Layout::instance()->importResources();
    QFont splash = QFont("Freshman", 42, QFont::Bold);
    QFont homeButtons = QFont("Freshman", 12);
    ui->label_home_splash->setFont(splash);
    ui->pushButton_pages_home->setFont(homeButtons);
    ui->pushButton_pages_view->setFont(homeButtons);
    ui->pushButton_pages_plan->setFont(homeButtons);
    ui->pushButton_pages_admin->setFont(homeButtons);
    ui->pushButton_pages_exit->setFont(homeButtons);
    /*----End Fonts----*/
}
void MainWindow::clearButtons() // resets most program states
{
    // home pages
    ui->pushButton_pages_home->setDisabled(false);
    ui->pushButton_pages_view->setDisabled(false);
    ui->pushButton_pages_plan->setDisabled(false);
    ui->pushButton_pages_admin->setDisabled(false);

    // view page
    ui->comboBox_list_sort->setCurrentIndex(NOSORT);
    ui->comboBox_list_filterteams->setCurrentIndex(ALLTEAMS);
    ui->comboBox_list_filterstadiums->setCurrentIndex(ALLSTADIUMS);
    clearViewLabels();


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
    ui->pushButton_edit_delete->setDisabled(true);
    ui->pushButton_edit_add->setDisabled(false);

    // line edits
    ui->lineEdit_edit_souvenir_name->clear();
    ui->lineEdit_edit_souvenir_price->clear();
    ui->lineEdit_edit_souvenir_team->clear();
    ui->lineEdit_login_password->clear();
    ui->lineEdit_login_username->clear();
	ui->lineEdit_edit_stadium_capacity->clear();
	ui->lineEdit_edit_stadium_location->clear();
	ui->lineEdit_edit_stadium_name->clear();
	ui->lineEdit_edit_stadium_roof->clear();
	ui->lineEdit_edit_stadium_surface->clear();
}

void MainWindow::clearViewLabels()
{
    ui->label_list_totalcapacity->hide();
    ui->label_list_totalgrass->hide();
    ui->label_list_totalroofs->hide();
}

void MainWindow::on_pushButton_edit_add_clicked() // admin add button
{
    ui->formWidget_edit_souvenir->setDisabled(false);
    ui->formWidget_edit_stadium->setDisabled(false);
    ui->pushButton_edit_add->setDisabled(true);
    ui->pushButton_edit_cancel->setDisabled(false);

	if (ui->stackedWidget_edit->currentIndex() == EDITSTAD) {
		ui->lineEdit_edit_stadium_team->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_stadium_name->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_stadium_capacity->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,255}"), this));
		ui->lineEdit_edit_stadium_location->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_stadium_surface->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_stadium_roof->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
	} else if (ui->stackedWidget_edit->currentIndex() == EDITSOUV) {
		ui->lineEdit_edit_souvenir_team->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_souvenir_name->setValidator(new QRegExpValidator(QRegExp("[A-Za-z_ ]{0,255}"), this));
		ui->lineEdit_edit_souvenir_price->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,255}[.]{1}[0-9]{0,2}"), this));
	}
    // code + error checking

    ui->pushButton_edit_confirm->setDisabled(false);

}

void MainWindow::on_tableWidget_edit_cellClicked(int row, int col)
{
	static int rowStat;
	static int colStat;
	rowStat = row;
	colStat = col;

	ui->pushButton_edit_delete->setDisabled(false);
	connect(ui->pushButton_edit_delete, &QPushButton::clicked, [this]() {
		emit this->EmittedDelSignal(rowStat, colStat);
	});
	connect(this, &MainWindow::EmittedDelSignal, this, &MainWindow::ProcessDelete);
}

#define table(row, column) ui->tableWidget_edit->item(row, column)->text()
void MainWindow::ProcessDelete(int row, int /*col*/)
{
	disconnect(ui->pushButton_edit_delete, &QPushButton::clicked, nullptr, nullptr);
	disconnect(this, &MainWindow::EmittedDelSignal, this, &MainWindow::ProcessDelete);

	QString teamName;
	QString item = table(row, table->A_ITEM);
	for (int i = row; i >= 0; i--) {
		if (table(i, table->A_TEAMNAME_SOUVENIR) != QString{}) {
			teamName = table(i, table->A_TEAMNAME_SOUVENIR);
			break;
		}
	}

	DBManager::instance()->DeleteSouvenir(teamName, item);
	table->InitializeAdminEditTable(ui->tableWidget_edit);
	table->PopulateAdminEditTable(ui->tableWidget_edit);
}

void MainWindow::on_tableWidget_edit_doubleClicked(const QModelIndex &index)
{
	static QString temp;
	temp = index.data().toString();

	connect(ui->tableWidget_edit, &QTableWidget::cellChanged, [this](int row, int column) {
		emit this->EmittedSignal(row, column, temp);
	});

	connect(this, &MainWindow::EmittedSignal, this, &MainWindow::UpdateTable);
}

#define table(row, column) ui->tableWidget_edit->item(row, column)->text()
void MainWindow::UpdateTable(int row, int column, QString prev)
{
	disconnect(this, &MainWindow::EmittedSignal, this, &MainWindow::UpdateTable);
	disconnect(ui->tableWidget_edit, &QTableWidget::cellChanged, nullptr, nullptr);

	QString entry = table(row, column);

	if (!isValid(entry, prev)) {
		ui->tableWidget_edit->item(row, column)->setText(prev);
		QMessageBox::warning(this, tr("Warning"),
							 tr("That query was not valid, please try again"));
	} else {
		QString teamName;
		QString item = table(row, column - 1);
		for (int i = row; i >= 0; i--) {
			if (table(i, 1) != QString{}) {
				teamName = table(i, 1);
				break;
			}
		}

		DBManager::instance()->UpdateSouvenirPrice(teamName,
						   table(row, column - 1), table(row, column));
	}
}
#undef table

bool MainWindow::isValid(QString cur, QString prev)
{
	bool isNum;
	cur.toDouble(&isNum);
	QRegExp regNum("[0-9]{0,255}[.]{1}[0-9]{0,2}");
	QRegExp regStr("[A-Za-z_ ]{0,255}");
	if (regNum.exactMatch(prev)) {
		if (regNum.exactMatch(cur)) {
			return true;
		} else {
			return false;
		}
	} else if (regStr.exactMatch(prev)) {
		return false;
//		if (regStr.exactMatch(cur)) {
//			return true;
//		} else {
//			return false;
//		}
	}
	qDebug() << "Something went wrong: MainWindow::isValid(QString cur, QString prev)";
	assert(false);
}

void MainWindow::on_pushButton_edit_confirm_clicked()
{
	if (ui->stackedWidget_edit->currentIndex() == EDITSOUV) {
		QString teamName = ui->lineEdit_edit_souvenir_team->text();
		QString item = ui->lineEdit_edit_souvenir_name->text();
		QString price = ui->lineEdit_edit_souvenir_price->text();

		QStringList list;

		DBManager::instance()->GetTeams(list);

		if (!list.contains(teamName) || item.isEmpty() || price.isEmpty()) {
			QMessageBox::warning(this, tr("Notice"),
					tr("There was an error with your query.\nPlease try again."));
		} else {
			DBManager::instance()->AddSouvenir(teamName, item, price);
			table->InitializeAdminEditTable(ui->tableWidget_edit);
			table->PopulateAdminEditTable(ui->tableWidget_edit);
		}
	}
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

    table->showTeamNames(ui->tableView_plan_custom);

    // planning logic

    ui->pushButton_plan_continue->setDisabled(false);
}

void MainWindow::on_pushButton_plan_MST_clicked()
{
    clearButtons();
    ui->pushButton_plan_MST->setDisabled(true);
}

/*----END HELPER FUNCTIONS----*/

void MainWindow::populateStadiumInfo(int sortIndex, int teamFilterIndex, int stadiumsFilterIndex)
{

    if (sortIndex < 0 || teamFilterIndex < 0 || stadiumsFilterIndex < 0)
        return;

    clearViewLabels();

    int capacity = 0;
    int openRoofCount = 0;

    QString sort[] = {"None","teamNames", "conference","stadiumName", "dateOpen", "seatCap"};

    QSqlQuery query;
    QString queryString = "SELECT (SELECT teams.teamNames FROM teams WHERE teams.id = information.id) as teamNames, stadiumName,seatCap,conference,division,surfaceType,roofType,dateOpen FROM information";

    switch(teamFilterIndex)
    {
    case 1: queryString+= " WHERE division LIKE '%" + filterTeams[teamFilterIndex] + "%'";
            break;
    case 2: queryString+= " WHERE division LIKE '%" + filterTeams[teamFilterIndex] + "%'";
            break;
    case 3: queryString+= " WHERE division = '" + filterTeams[teamFilterIndex] + "'";
            break;
    case 4: queryString+= " WHERE surfaceType = '" + filterTeams[teamFilterIndex] + "'";
            break;
    default: break;
    }




     if (stadiumsFilterIndex == OPENROOF)
     {
        if (teamFilterIndex==0)
            queryString+= " WHERE roofType = 'Open' ";
        else
            queryString+= " AND roofType = 'Open'";
     }

     QString queryStringWithoutOrder = queryString;
     if (sortIndex != 0)
        queryString += " ORDER BY " + sort[sortIndex] + " ASC";


    query.exec(queryString);


    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Team Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Stadium Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Seat Cap"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Conference"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Division"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Surface Type"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Roof Type"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date Open"));

    ui->tableView_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_list->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_list->setModel(model);

    QLocale c(QLocale::C);  // to set the string with "," (ex: 12,500) into int
    query.exec(queryStringWithoutOrder + " GROUP BY stadiumName");
    while(query.next())
    {

        capacity += c.toInt(query.value(2).toString());
        if (query.value(6).toString() == "Open")
            openRoofCount++;
    }

    if (sortIndex == CAPACITY)
    {
        ui->label_list_totalcapacity->setText("Total Capacity: " + QString("%L1").arg(capacity));
        ui->label_list_totalcapacity->show();
    }

    if (teamFilterIndex == BERMUDAGRASS)
    {
        ui->label_list_totalgrass->setText("Total Bermuda Grass Teams: " + QString::number(ui->tableView_list->model()->rowCount()));
        ui->label_list_totalgrass->show();
    }

    if (stadiumsFilterIndex == OPENROOF)
    {
        ui->label_list_totalroofs->setText("Total Open Roof Stadiums: " + QString::number(openRoofCount));
        ui->label_list_totalroofs->show();
    }


}

void MainWindow::populateTeams()
{
    QStringList teamList;
    DBManager::instance()->GetTeams(teamList);

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
    table->showTeamInfo(ui->tableView_search_info, index.data().toString());

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


void MainWindow::on_comboBox_list_sort_currentIndexChanged(int index)
{
    populateStadiumInfo(index, ui->comboBox_list_filterteams->currentIndex(), ui->comboBox_list_filterstadiums->currentIndex());
}

void MainWindow::on_comboBox_list_filterteams_currentIndexChanged(int index)
{
    populateStadiumInfo(ui->comboBox_list_sort->currentIndex(), index, ui->comboBox_list_filterstadiums->currentIndex());
}

void MainWindow::on_comboBox_list_filterstadiums_currentIndexChanged(int index)
{
    populateStadiumInfo(ui->comboBox_list_sort->currentIndex(), ui->comboBox_list_filterteams->currentIndex(), index);
}
