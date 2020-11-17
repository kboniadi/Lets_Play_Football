#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBManager;
class TableManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

        void on_pushButton_admin_edit_clicked();

        void on_comboBox_edit_activated(int index);

    void on_pushButton_pages_exit_clicked();
    /*----END NAVIGATION----*/

    /*----HELPER FUNCTIONS----*/
    void initializeLayout();

    void clearButtons();

    void clearViewLabels();

    void on_pushButton_edit_add_clicked();

    void on_pushButton_edit_confirm_clicked();

    void on_pushButton_edit_cancel_clicked();

    void on_pushButton_plan_packers_clicked();

    void on_pushButton_plan_patriots_clicked();

    void on_pushButton_plan_rams_clicked();

    void on_pushButton_plan_vikings_clicked();

    void on_pushButton_plan_custom_clicked();

    void on_pushButton_plan_MST_clicked();
    /*----END HELPER FUNCTIONS----*/

    //Populate table for stadium view
    void populateStadiumInfo(int sortIndex, int teamFilterIndex, int stadiumFilterIndex);

    //Populate table for team search view
    void populateTeams();

    //Handle double click on team search view
    void on_tableView_search_teams_doubleClicked(const QModelIndex &index);

    //Populate souvenir table for selected team search
    void populateSouvenirs(QString team);

    //Control sort combobox
    void on_comboBox_list_sort_currentIndexChanged(int index);

    //Control team filter combobox
    void on_comboBox_list_filterteams_currentIndexChanged(int index);

    //Control stadium filter combobox
    void on_comboBox_list_filterstadiums_currentIndexChanged(int index);
	
	void on_pushButton_import_clicked();

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
};
#endif // MAINWINDOW_H
