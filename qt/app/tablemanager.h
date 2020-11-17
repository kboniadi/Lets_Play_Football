#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QDebug>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableView>
#include <QVector>
#include <QHeaderView>
#include <QStringListModel>
#include "dbmanager.h"

/*!
 * @class TableManager
 * @brief The TableManager holds attributes for all tables, initializes them,
 * and populates their contents. For use in all program functionality
 */
class TableManager {
public:

	/*!
	 * @brief Default TableManager object constructor
	 */
	TableManager() = default;

	/*!
	 * @brief Destructor
	 */
	~TableManager() = default;

	/*!
	 * @brief Deleted copy constructor
	 */
	TableManager(const TableManager&) = delete;

	/*!
	 * @brief Deleted copy assignment
	 */
	TableManager& operator=(const TableManager&) = delete;

	// ************************* Admin Info Table Attributes ************************

	/// Number of columns in table
	const int ADMIN_TABLE_INFO_COL_COUNT = 9;
	/// positions of admin table columns by name
	enum AdminTableInfoColPositions	{ A_TEAMNAME, A_STADIUMNAME, A_SEATCAP, A_LOCATION, A_CONFERENCE, A_DIVISION, A_SURFACETYPE, A_ROOFTPYE, A_DATEOPEN };
	/// Names of admin table column headers
	QStringList adminTableInfoColNames = { "Team Name", "Stadium Name", "Seat Cap", "Location", "Conference", "Division", "Surface Type", "Roof Type", "Date Open" };

	// ************************* Admin distance Table Attributes ************************

	/// Number of columns in table
	const int ADMIN_TABLE_Distance_COL_COUNT = 4;
	/// positions of admin table columns by name
	enum AdminTableDistColPositions	{ A_TEAMNAME2, A_BEGINSTADIUM, A_ENDSTADIUM, A_DISTANCETO };
	/// Names of admin table column headers
	QStringList adminTableDistColNames = { "Team Name", "Starting Stadium", "Ending Stadium", "Distance To" };

	// ************************* Admin Souvenir Table Attributes ************************

	/// Number of columns in table
	const int ADMIN_TABLE_Souvenir_COL_COUNT = 4;
	/// positions of admin table columns by name
	enum AdminTableSouvColPositions	{ AS_KEY, A_TEAMNAME3, A_ITEM, A_PRICE };
	/// Names of admin table column headers
	QStringList adminTableSouvColNames = { "Key", "Team Name", "Item", "Price" };

						/***********
						 * Methods *
						 ***********/

	// *********************** Team Search Table Methods ****************************

//	/*!
//	 * @brief Initializes cities table to blank
//	 * @param citiesTable; Table to be initialized
//	 * @param cityTablecols; Number of columns in table
//	 * @param cityTableHeaders; Table's column header names
//	 */
//	void InitializeSearchTable(QTableWidget* teamsTable, const int &teamTablecols, const QStringList &teamTableHeaders);

//	/*!
//	 * @brief Populates cities table with relevant information
//	 * @param cityTable; Table to be initialized
//	 * @param cityNames; Number of columns in table
//	 * @param distancesFromBerlin; List of distances of each city to Berlin
//	 */
//	void PopulateSearchTable(QTableWidget* teamsTable, QStringList *teamsNames, QVector<int> *distancesFromBerlin);

//	// ************************* Food Table Methods ****************************

//	/*!
//	 * @brief Initializes foods table to blank
//	 * @param table; Table to be initialized
//	 * @param cols; Number of columns in table
//	 * @param headers; Table's column header names
//	 */
//	void InitializeFoodTable(QTableWidget* table, const int &cols, const QStringList &headers);

//	/*!
//	 * @brief Populates foods table with relevant information
//	 * @param foodTable; Table to be initialized
//	 * @param cities; City objects with which to populate table
//	 */
//	void PopulateFoodTable(QTableWidget* foodTable, QVector<int> *cities);

//	// **************** Trip Planning Table Methods ****************************

//	/*!
//	 * @brief Populates trip planning table with relevant information
//	 * @param table; Table to be initialized
//	 * @param cities; City objects with which to populate table
//	 */
//	void PopulateTripTable(QTableView* table, const QStringList& cities);

//	// ************** Food Purchasing Table Methods ****************************

//	/*!
//	 * @brief Initializes purchases table to blank
//	 * @param table; Table to be initialized
//	 * @param cols; Number of columns in table
//	 * @param headers; Table's column header names
//	 */
//	void InitializePurchaseTable(QTableWidget* table, const int &cols, const QStringList &headers);

//	/*!
//	 * @brief Populates purchase table with relevant information
//	 * @param purchaseTable; Table to be initialized
//	 * @param cities; City objects with which to populate table
//	 */
//	void PopulatePurchaseTable(QTableWidget* purchaseTable, QVector<int>* cities);

//	/*!
//	 * @brief Inserts a dynamic spinbox in table at specific column
//	 * @param table; Table in which to insert spinbox column
//	 * @param min; Minimum value allowed in spinbox
//	 * @param max; Maximum value allowed in spinbox
//	 * @param col; Column location to insert spinbox column
//	 */
//	void InsertSpinBoxCol(QTableWidget* table, const int min, const int max, const int col);

//	// ********************** Receipt Table Methods ****************************

//	/*!
//	 * @brief Initializes receipt table to blank
//	 * @param receiptTable; Table to be initialized
//	 * @param cols; Number of columns in table
//	 * @param headers; Table's column header names
//	 */
//	void InitializeReceiptTable(QTableWidget* receiptTable, const int &cols, const QStringList &headers);

//	/*!
//	 * @brief Populates receipt table with relevant information
//	 * @param receiptTable; Table to be initialized
//	 * @param cities; City objects with which to populate table
//	 */
//	void PopulateReceiptTable(QTableWidget* receiptTable, QVector<int>* cities);

	// ****************** Admin Table Table Methods ****************************
	/*!
	 * @brief Initializes admin table using model for city distance list
	 * @param table; Table to be initialized
	 */
	void AdminInfoTable(QTableView* table);

	void AdminDistTable(QTableView *table);

	void AdminSouvTable(QTableView *table);

	/*!
	 * @brief Initializes admin table manually
	 * @param adminTable; Table to be initialized
	 * @param cols; Number of columns in table
	 * @param headers; Table's column header names
	 */
	void InitializeAdminEditTable(QTableWidget* table);

	/*!
	 * @brief Populates admin table with relevant information
	 * @param table; Table to be initialized
	 * @param cities; City objects with which to populate table
	 */
	void PopulateAdminEditTable(QTableWidget* table);

	/*!
	 * @brief Deletes all rows in table
	 * @param table; Table to be deleted
	 */
	void DeleteAllTableRows(QTableWidget *table);
};

#endif // TABLEMANAGER_H
