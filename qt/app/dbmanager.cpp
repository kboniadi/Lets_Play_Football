#include "dbmanager.h"

DBManager::DBManager(QWidget *parent)
	: QWidget{parent}, QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
	setDatabaseName(QDir::currentPath() + "/Data.db");

	// Print error if database does not open
	if (!open()) {
		qDebug() << "Connection to database failed";
	} else {
		qDebug() << "Connection to database succeeded";
	}
}

DBManager::~DBManager()
{
	// Output when database closes
	if (open()) {
		qDebug() << "Connection to database has been closed";
		QSqlDatabase::close();
	}
}

DBManager* DBManager::instance()
{
	// Create one and only one instance of the database
	static DBManager instance;
	return &instance;
}
