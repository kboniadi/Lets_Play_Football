#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QDebug>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableView>
#include <QVector>
#include <QHeaderView>
#include <QStringListModel>

class DBManager;
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
	enum AdminTableInfoColPositions	{ A_TEAMNAME_INFO, A_STADIUMNAME, A_SEATCAP, A_LOCATION, A_CONFERENCE, A_DIVISION, A_SURFACETYPE, A_ROOFTPYE, A_DATEOPEN };
	/// Names of admin table column headers
	QStringList adminTableInfoColNames = { "Team Name", "Stadium Name", "Seat Cap", "Location", "Conference", "Division", "Surface Type", "Roof Type", "Date Open" };

	// ************************* Admin distance Table Attributes ************************

	/// Number of columns in table
	const int ADMIN_TABLE_Distance_COL_COUNT = 4;
	/// positions of admin table columns by name
	enum AdminTableDistColPositions	{ A_TEAMNAME_DISTANCE, A_BEGINSTADIUM, A_ENDSTADIUM, A_DISTANCETO };
	/// Names of admin table column headers
	QStringList adminTableDistColNames = { "Team Name", "Starting Stadium", "Ending Stadium", "Distance To" };

	// ************************* Admin Souvenir Table Attributes ************************

	/// Number of columns in table
	const int ADMIN_TABLE_Souvenir_COL_COUNT = 4;
	/// positions of admin table columns by name
	enum AdminTableSouvColPositions	{ AS_KEY, A_TEAMNAME_SOUVENIR, A_ITEM, A_PRICE };
	/// Names of admin table column headers
	QStringList adminTableSouvColNames = { "Key", "Team Name", "Item", "Price" };

						/***********
						 * Methods *
						 ***********/

	// ****************** Admin Table Table Methods ****************************
	/*!
	 * @brief Initializes admin table using model for city distance list
	 * @param table; Table to be initialized
	 */
	void AdminInfoTable(QTableView* table);

	void InitializeAdminInfoEditTable(QTableWidget* table);
	void PopulatedAdminInfoEditTable(QTableWidget* table);

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
    /*!
     * @brief Shows team info on team search [age
     * @param table; Table to be displayed
     * @param teamName; name of teams whos info will be displayed
     */
    void showTeamInfo(QTableView * table, QString teamName);
    /*!
     * @brief shows list of teams user can visit
     * @param table; Table to be displayed
     */
    void showTeamNames(QTableView * table);
};

#endif // TABLEMANAGER_H
