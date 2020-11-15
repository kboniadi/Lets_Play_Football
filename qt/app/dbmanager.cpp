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

bool DBManager::checkLogin(const QString &username, const QString &password)
{
    // Prep initial login bool
    bool found = false;

    // Prep query
    query.prepare("SELECT * FROM accounts WHERE username = :username AND password = :password AND level = 'ADMIN';");

    // Bind values safely
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    // If query executes successfully, check values
    if(query.exec())
    {
        // If values are correct, login
        if(query.next())
        {
            found = true;
            qDebug() << "Login Successful";
        }
    }
    else // If query fails, print failure
    {
        qDebug() << "Login Query Failed";
    }

    return found;
}
