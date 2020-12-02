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
    MainWindow(QWidget *parent = nullptr);
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

	//Used to set the total Distance for the LA rams BFS
	void laRams();

	//Populate table for stadium view
	void populateStadiumInfo(int sortIndex, int teamFilterIndex, int stadiumFilterIndex);

	//Populate table for team search view
	void populateTeams();

	//Populate souvenir table for selected team search
	void populateSouvenirs(QString team);

	void recursiveAlgo(QString start, QStringList& selectedList, QStringList& availableList, long& distance);

	bool isValid(QString cur, QString prev);

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

	void on_tableWidget_edit_cellClicked(int row, int column);
	void ProcessDelete(int row, int col);
	void on_tableWidget_edit_doubleClicked(const QModelIndex &index);
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
	void EmittedSignal(int row, int col, QString prev);
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
    QStringList sort = { "None", "Team Name", "Conference Name", "Stadium Name", "Date Opened", "Capacity" };
    QStringList filterTeams = { "All", "AFC", "NFC", "NFC North", "Bermuda Grass" };
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
