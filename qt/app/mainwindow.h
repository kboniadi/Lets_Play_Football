#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBManager;

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
    /*----END NAVIGATION----*/


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
        EDIT
    };
    /*----END NAVIGATION ENUMS----*/

	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
