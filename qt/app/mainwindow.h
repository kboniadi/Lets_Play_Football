#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QLabel>
#include "dbmanager.h"
#include <bfs.h>
#include "unordered_map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBManager;
class TableManager;
class Layout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/*!
	 * @brief Default MainWindow object constructor
	 * @param parent; Pointer to parent object (null)
	 */
    MainWindow(QWidget *parent = nullptr);

	/*!
	 * @brief Destructor
	 */
    ~MainWindow();
private:
	/*----HELPER FUNCTIONS----*/
	void SetStatusBar(const QString & messg, int timeout = 0);

	void SetAdminPurchaseDropDown();

	void initializeLayout();

	void setResources();

	void clearButtons();

	void clearViewLabels();

	long calculateDistance(QStringList);

	void CreateReceipt(QVector<Souvenir>& souvenirs);


    /*!
     * @brief preforms a bfs and displays the total distance travelled
     */
	void laRams();

    /**
     * @brief Populate the stadium table with the right sort and filter condition
     * @param sortIndex: int storing the sort condition
     * @param teamFilterIndex: int storing the team filter condition
     * @param stadiumFilterIndex: int storing the stadium filter condition
     */
    void populateStadiumInfo(int sortIndex, int teamFilterIndex, int stadiumFilterIndex);

    /**
     * @brief Populate the list of teams for display
     */
    void populateTeams();

    /**
     * @brief Populate the souvenirs of the team being selected
     * @param team: team that contains the souvenirs info
     */
    void populateSouvenirs(QString team);

    /**
     * @brief Calculate and select the shortest distance from start location
     * @param start: starting location
     * @param selectedList: list storing the current in correct order trip
     * @param availableList: list storing the list to be sorted
     * @param distance: total distance for the trip
     */
	void recursiveAlgo(QString start, QStringList& selectedList, QStringList& availableList, long& distance);

	/*!
	 * \brief isValid
	 * \param cur; new value
	 * \param prev; old value
	 * \return bool
	 */
	bool isValid(QString cur, QString prev);

	/*!
	 * \brief toUpperCase
	 * \param str; un-modified string
	 * \return string with upper case starting words
	 */
	QString toUpperCase(const QString &str);
	/*----END HELPER FUNCTIONS----*/
private slots:
    /*----NAVIGATION----*/
    void on_pushButton_pages_home_clicked();

    void on_pushButton_pages_view_clicked();

        void on_pushButton_view_search_clicked();

        void on_pushButton_view_list_clicked();

    void on_pushButton_pages_plan_clicked();

        void on_pushButton_plan_continue_clicked();

        void on_pushButton_pos_cancel_clicked();

        void on_pushButton_pos_continue_clicked();

        void on_pushButton_receipt_continue_clicked();

    void on_pushButton_pages_admin_clicked();

        void on_pushButton_login_clicked();

        void on_pushButton_admin_import_clicked();

		void on_pushButton_import_clicked();

        void on_pushButton_admin_edit_clicked();

        void on_pushButton_admin_receipts_clicked();

        void on_comboBox_edit_activated(int index);

    void on_pushButton_pages_exit_clicked();
    /*----END NAVIGATION----*/

    void on_pushButton_edit_add_clicked();

    void on_pushButton_edit_confirm_clicked();

    void on_pushButton_edit_cancel_clicked();

    void on_pushButton_plan_packers_clicked();

    void on_pushButton_plan_patriots_clicked();

    void on_pushButton_plan_custom_clicked();

    //Handle double click on team search view
    void on_tableView_search_teams_doubleClicked(const QModelIndex &index);

    //Control sort combobox
    void on_comboBox_list_sort_currentIndexChanged(int index);

    //Control team filter combobox
    void on_comboBox_list_filterteams_currentIndexChanged(int index);

    //Control stadium filter combobox
    void on_comboBox_list_filterstadiums_currentIndexChanged(int index);

	/*!
	 * \brief on_tableWidget_edit_cellClicked slot on edit table click
	 * \param row; index
	 * \param column; index
	 */
	void on_tableWidget_edit_cellClicked(int row, int column);

	/*!
	 * \brief ProcessDelete slot to process delete
	 * \param row; index
	 * \param col; index
	 */
	void ProcessDelete(int row, int col);

	/*!
	 * \brief on_tableWidget_edit_doubleClicked on edit table click
	 * \param index
	 */
	void on_tableWidget_edit_doubleClicked(const QModelIndex &index);

	/*!
	 * \brief UpdateTable
	 * \param row; index
	 * \param col; index
	 * \param prev; previous value at (row, column)
	 */
	void UpdateTable(int row, int col, QString prev);

	void on_tableView_edit_doubleClicked(const QModelIndex &index);

    void on_pushButton_plan_add_clicked();

    void on_pushButton_plan_remove_clicked();

    void on_pushButton_plan_sort_clicked();

	void on_comboBox_admin_receipts_currentIndexChanged(int index);

//    void on_comboBox_admin_receipts_currentIndexChanged(int index);

public slots:
    void updateCartTotal();

signals:
	/*!
	 * \brief EmittedSignal
	 * \param row; index
	 * \param col; index
	 * \param prev; previous value at (row, column)
	 */
	void EmittedSignal(int row, int col, QString prev);

	/*!
	 * \brief EmittedDelSignal
	 * \param row; index
	 * \param col; index
	 */
	void EmittedDelSignal(int row, int col);
private:
    /*----NAVIGATION ENUMS----*/
    enum Pages
    {
        HOME,
        VIEW,
        PLAN,
        POS,
        RECEIPT,
        LOGIN,
        ADMIN
    };

    enum ViewPages
    {
        SEARCH,
        LIST
    };

    enum AdminPages
    {
        IMPORT,
		EDIT,
        RECEIPTS
    };

    enum Sort
    {
        NOSORT,
        TEAMNAME,
        CONFERENCENAME,
        STADIUMNAME,
        DATEOPENED,
        CAPACITY
    };

    enum FilterTeams
    {
        ALLTEAMS,
        AFC,
        NFC,
        NFCNORTH,
        BERMUDAGRASS
    };

    enum FilterStadiums
    {
        ALLSTADIUMS,
        OPENROOF
    };
	enum AdminEdit {
		EDITSOUV,
		EDITSTAD
	};

    /*----END NAVIGATION ENUMS----*/

    /*----DIRECTORY COMBO BOXES----*/
	QStringList sort = { "None", "Team Name", "Conference Name",
						 "Stadium Name", "Date Opened", "Capacity" };
	QStringList filterTeams = { "All", "AFC", "NFC", "NFC North",
								"Bermuda Grass" };
    QStringList filterStadiums = { "All", "Open Roof" };
    /*----END DIRECTORY COMBO BOXES----*/

	Ui::MainWindow *ui;
	TableManager *table;
	QLabel status;

    QStringList availableTeams;
    QStringList selectedTeams;

    nonstd::unordered_map<int,Souvenir> souvenirList;
};

#endif // MAINWINDOW_H
