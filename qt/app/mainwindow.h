#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void setResources();

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

    enum SortTeams
    {
        NOTEAMSORT,
        TEAMNAME,
        CONFERENCENAME
    };

    enum SortStadiums
    {
        NOSTADIUMSORT,
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
    QStringList sortTeams = { "None", "Team Name", "Conference Name" };
    QStringList sortStadiums = { "None", "Stadium Name", "Date Opened", "Capacity" };
    QStringList filterTeams = { "All", "AFC", "NFC", "NFC North", "Bermuda Grass" };
    QStringList filterStadiums = { "All", "Open Roof" };
    /*----END DIRECTORY COMBO BOXES----*/

	Ui::MainWindow *ui;
	TableManager *table;
};
#endif // MAINWINDOW_H
