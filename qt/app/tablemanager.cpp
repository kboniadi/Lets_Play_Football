#include "tablemanager.h"
#include "dbmanager.h"

void TableManager::AdminInfoTable(QTableView *table)
{
	QSqlQueryModel *model = new QSqlQueryModel;

	model->setQuery("SELECT teamNames, stadiumName, seatCap, location, "
					"conference, division, surfaceType, roofType, dateOpen "
					"FROM information, teams WHERE teams.id = information.id "
					"ORDER BY teams.id");

	if (!model->query().exec())
		qDebug() << "TableManager::InitializeAdminInfoTable() : query failed";

	model->setHeaderData(0, Qt::Horizontal, adminTableInfoColNames[0], Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, adminTableInfoColNames[1], Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, adminTableInfoColNames[2], Qt::DisplayRole);
	model->setHeaderData(3, Qt::Horizontal, adminTableInfoColNames[3], Qt::DisplayRole);
	model->setHeaderData(4, Qt::Horizontal, adminTableInfoColNames[4], Qt::DisplayRole);
	model->setHeaderData(5, Qt::Horizontal, adminTableInfoColNames[5], Qt::DisplayRole);
	model->setHeaderData(6, Qt::Horizontal, adminTableInfoColNames[6], Qt::DisplayRole);
	model->setHeaderData(7, Qt::Horizontal, adminTableInfoColNames[7], Qt::DisplayRole);
	model->setHeaderData(8, Qt::Horizontal, adminTableInfoColNames[8], Qt::DisplayRole);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setModel(model);
}

void TableManager::AdminDistTable(QTableView *table)
{
	QSqlQueryModel *model = new QSqlQueryModel;

	model->setQuery("SELECT teamNames, beginStadium, endStadium, distanceTo "
					"FROM distance, teams WHERE teams.id = distance.id "
					"ORDER BY teams.id");

	if (!model->query().exec())
		qDebug() << "TableManager::InitializeAdminDistTable() : query failed";

	model->setHeaderData(0, Qt::Horizontal, adminTableDistColNames[0], Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, adminTableDistColNames[1], Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, adminTableDistColNames[2], Qt::DisplayRole);
	model->setHeaderData(3, Qt::Horizontal, adminTableDistColNames[3], Qt::DisplayRole);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setModel(model);
}

void TableManager::AdminSouvTable(QTableView *table)
{
	QSqlQueryModel *model = new QSqlQueryModel;

	model->setQuery("SELECT teamNames, items, price FROM souvenir, teams "
					"WHERE teams.id = souvenir.id ORDER BY teams.id");

	if (!model->query().exec())
		qDebug() << "TableManager::InitializeAdminSouvTable() : query failed";

	model->setHeaderData(0, Qt::Horizontal, adminTableSouvColNames[0], Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, adminTableDistColNames[1], Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, adminTableDistColNames[2], Qt::DisplayRole);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setModel(model);
}

void TableManager::InitializeAdminEditTable(QTableWidget *table)
{
	table->clearContents();
	table->setColumnCount(ADMIN_TABLE_Souvenir_COL_COUNT);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setHorizontalHeaderLabels(adminTableSouvColNames);
	// TODO - Might be a good idea to set column widths here
	table->setEditTriggers(QTableView::NoEditTriggers);
	table->hideColumn(AS_KEY);
	table->verticalHeader()->hide();

	DeleteAllTableRows(table);
}

#define db DBManager::instance()
void TableManager::PopulateAdminEditTable(QTableWidget *table)
{
	QTableWidgetItem* priceItem;
	QString currentName;
	QString previousName;
	QStringList teams;
	QStringList souvenirs;

	db->GetTeams(teams);

	// For the length of the city list
	for(int i = 0; i < teams.size(); i++)
	{
		int numSouvenir = db->GetNumSouvenir(teams[i]);
		souvenirs.clear();
		db->GetSouvenirs(teams[i], souvenirs);

		// Iterate through each city's food list
		for(int j = 0; j < numSouvenir; j++)
		{
			// Generate item price tablewidget item
			priceItem = new QTableWidgetItem(db->SouvenirNameToPrice(teams[i], souvenirs[j]));

			// If list is not empty
			if(table->rowCount() != 0)
			{
				// Check to see if there's a match between this row's city name and the previous row's city name
				currentName = table->item(table->rowCount() -1, AS_KEY)->data(0).toString();
				previousName = teams[i];

				// Add a row to the end
				table->insertRow(table->rowCount());

				bool match = currentName == previousName;

				// If the row names do not match, insert the city name into the name column
				if(!match)
				{
					// Insert city name into city name column
					table->setItem(table->rowCount() - 1, A_TEAMNAME3, new QTableWidgetItem(teams[i]));
				}
				else // Else, insert blank name
				{
					table->setItem(table->rowCount() - 1, A_TEAMNAME3, new QTableWidgetItem(""));
				}
			} // END if purchase table not empty
			else // if purchase table empty
			{
				// Add new row
				table->insertRow(table->rowCount());

				// Insert city name into city name column
				table->setItem(table->rowCount() - 1, A_TEAMNAME3, new QTableWidgetItem(teams[i]));
			}

			// Insert city name into key column
			table->setItem(table->rowCount() - 1, AS_KEY, new QTableWidgetItem(teams[i]));
			// Add food name
			table->setItem(table->rowCount() - 1, A_ITEM, new QTableWidgetItem(souvenirs[j]));
			// Add food price
			table->setItem(table->rowCount() - 1, A_PRICE, priceItem);

		} // END for iterate through food list
	} // END for iterate through city list
}

// Deletes contents of passed in table
void TableManager::DeleteAllTableRows(QTableWidget *table)
{
	const int ROW_COUNT = table->rowCount();

	for(int index = 0; index < ROW_COUNT; index++)
	{
		table->removeRow(0);
	}
}
