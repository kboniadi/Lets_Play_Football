#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QMessageBox>

class DBManager: public QWidget, public QSqlDatabase {
	Q_OBJECT
public:
	/*!
	 * @brief Creates one instance of the database
	 * @return Pointer the the instance of the database class
	 */
	static DBManager* instance();

	/*!
	 * @brief Deleted copy constructor
	 */
	DBManager(const DBManager&) = delete;

	/*!
	 * @brief Deleted copy assignment
	 */
	DBManager& operator=(const DBManager&) = delete;

    /*!
     * @brief Compares user login to values in the database
     * @return bool representing successful login
     */
    bool checkLogin(const QString &username, const QString &password);

	void ImportTeams();
	void GetTeams(QStringList &teams);
private:
    QSqlQuery query;
	/*!
	 * @brief DBManager (private)
	 * @param parent; Linked to QWidget class
	 */
	explicit DBManager(QWidget *parent = nullptr);

	/*!
	 * @brief Destructor
	 */
	~DBManager();
	QStringList parser(QString &line, const char delim);
};
#endif // DBMANAGER_H
