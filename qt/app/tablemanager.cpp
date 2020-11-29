#include "tablemanager.h"
#include "dbmanager.h"
#include <bfs.h>

TableManager::TableManager()
{
    purchaseTableSpinBoxes = new QVector<QSpinBox*>;
}

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
	table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
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
	table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
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
	table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setModel(model);
}

void TableManager::InitializeAdminEditTable(QTableWidget *table)
{
	table->clearContents();
	table->setColumnCount(ADMIN_TABLE_Souvenir_COL_COUNT);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->setHorizontalHeaderLabels(adminTableSouvColNames);
	// TODO - Might be a good idea to set column widths here
	table->setEditTriggers(QTableView::DoubleClicked);
	table->setSelectionBehavior(QTableView::SelectRows);
	table->hideColumn(AS_KEY);
	table->verticalHeader()->hide();

	DeleteAllTableRows(table);
}

#define db DBManager::instance()
void TableManager::PopulateAdminEditTable(QTableWidget *table)
{
	QTableWidgetItem* priceItem;
	QTableWidgetItem *item;
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
			item = new QTableWidgetItem(db->SouvenirNameToPrice(teams[i], souvenirs[j]));
			// Generate item price tablewidget item
			priceItem = item;

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
					item = new QTableWidgetItem(teams[i]);
					item->setFlags(item->flags() & ~Qt::ItemIsEditable);
					// Insert city name into city name column
					table->setItem(table->rowCount() - 1, A_TEAMNAME_SOUVENIR, item);
				}
				else // Else, insert blank name
				{
					item = new QTableWidgetItem("");
					item->setFlags(item->flags() & ~Qt::ItemIsEditable);
					table->setItem(table->rowCount() - 1, A_TEAMNAME_SOUVENIR, item);
				}
			} // END if purchase table not empty
			else // if purchase table empty
			{
				// Add new row
				table->insertRow(table->rowCount());

				item = new QTableWidgetItem(teams[i]);
				item->setFlags(item->flags() & ~Qt::ItemIsEditable);
				// Insert city name into city name column
				table->setItem(table->rowCount() - 1, A_TEAMNAME_SOUVENIR, item);
			}

			item = new QTableWidgetItem(teams[i]);
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			// Insert city name into key column
			table->setItem(table->rowCount() - 1, AS_KEY, item);

			item = new QTableWidgetItem(souvenirs[j]);
			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			// Add food name
			table->setItem(table->rowCount() - 1, A_ITEM, item);
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

void TableManager::showTeamInfo(QTableView *table, QString teamName)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString query = "SELECT * FROM information WHERE id = (SELECT teams.id FROM teams WHERE teams.teamNames = '" + teamName + "')";
    model->setQuery(query);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->hideColumn(0);
    table->setModel(model);
}
void TableManager::showTeamNames(QTableView *table)
{
    QSqlQueryModel * model = new QSqlQueryModel;
    QString query = "SELECT teamNames FROM teams";
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Teams"));

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setModel(model);
}


void TableManager::showBFSTrip(QTableView *table, bfs &bfsObj)
{
    QStringListModel * model = new QStringListModel;
    model->setStringList(bfsObj.getBfsList());
    table->setModel(model);
}

void TableManager::showTeams(QTableView* table, QStringList& available)
{
    QStringListModel* model = new QStringListModel;
    model->setStringList(available);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setModel(model);
}

void TableManager::InitializePurchaseTable(QTableWidget* purchaseTable, const int &cols, const QStringList &headers)
{
    purchaseTable->clearContents();
    purchaseTable->setColumnCount(cols);
    purchaseTable->setHorizontalHeaderLabels(headers);
    purchaseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    purchaseTable->setEditTriggers(QTableView::NoEditTriggers);
    //purchaseTable->hideColumn(P_KEY);
    purchaseTable->verticalHeader()->hide();

    DeleteAllTableRows(purchaseTable);
}

void TableManager::PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<Souvenir>& teamSouvenirs)
{
    QTableWidgetItem* priceItem;
    QString currentName;
    QString previousName;

    // For the length of the city list
    //for(int teamIndex = 0; teamIndex < teamSouvenirs.size(); teamIndex++)
    //{
     //   int foodListSize = DBManager::instance
                //teamSouvenirs[teamIndex].size();
      //  qDebug() << foodListSize;

        // Iterate through each city's food list
    for(int index = 0; index < teamSouvenirs.size(); index++)
    {
            // Generate food price tablewidgetitem
        priceItem = new QTableWidgetItem(QString::number(teamSouvenirs[index].price, 'f', 2));

            // If list is not empty
        if(purchaseTable->rowCount() != 0)
        {
                // Check to see if there's a match between this row's city name and the previous row's city name
            currentName = DBManager::instance()->getTeamName(teamSouvenirs[index-1].teamID);
                    //purchaseTable->item(purchaseTable->rowCount() -1, 0)->data(0).toString();
            previousName = DBManager::instance()->getTeamName(teamSouvenirs[index].teamID);

                // Add a row to the end
            purchaseTable->insertRow(purchaseTable->rowCount());


            bool match = currentName == previousName;

                // If the row names do not match, insert the city name into the name column
            if(!match)
            {
                // Insert city name into city name column
                purchaseTable->setItem(purchaseTable->rowCount() - 1, 0, new QTableWidgetItem(DBManager::instance()->getTeamName(teamSouvenirs[index].teamID)));
            }
            else // Else, insert blank name
            {
                purchaseTable->setItem(purchaseTable->rowCount() - 1, 0, new QTableWidgetItem(""));
            }
        } // END if purchase table not empty
        else // if purchase table empty
        {
                // Add new row
            purchaseTable->insertRow(purchaseTable->rowCount());

                // Insert city name into city name column
            purchaseTable->setItem(purchaseTable->rowCount() - 1, 0, new QTableWidgetItem(DBManager::instance()->getTeamName(teamSouvenirs[index].teamID)));
        }

            // Insert city name into key column
            //purchaseTable->setItem(purchaseTable->rowCount() - 1, P_KEY, new QTableWidgetItem(cities->at(cityIndex).GetName()));
            // Add food name
        purchaseTable->setItem(purchaseTable->rowCount() - 1, 1, new QTableWidgetItem(teamSouvenirs[index].name));
            // Add food price
        purchaseTable->setItem(purchaseTable->rowCount() - 1, 2, priceItem);

        QString teamname = DBManager::instance()->getTeamName(teamSouvenirs[index].teamID);
        QString souName = teamSouvenirs[index].name;
        QString price = QString::number(teamSouvenirs[index].price);
    } // END for iterate through food list
    InsertSpinBoxCol(purchaseTable,0,100,3);
}

void TableManager::InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col)
{
    QSpinBox *sBox;

    purchaseTableSpinBoxes->clear();

    for(int row = 0; row < table->rowCount(); row++)
    {
        QString objectName = QString::number(row);

        sBox = new QSpinBox(table);
        //sBox->setObjectName(objectName);
        sBox->setRange(min, max);
        table->setCellWidget(row, col, sBox);
        purchaseTableSpinBoxes->append(sBox);
    }
}
void TableManager::clearTable(QTableView *table)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

}

double TableManager::UpdateTotalPrice(QTableWidget* table)
{
    double totalCost = 0;
    for (int i = 0; i < purchaseTableSpinBoxes->size(); i++)
        totalCost+= table->item(i,2)->data(0).toDouble() * (purchaseTableSpinBoxes->at(i)->value());
    return totalCost;
}
