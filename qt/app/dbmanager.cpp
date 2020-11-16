#include "dbmanager.h"
#include <QFileDialog>
#include <QElapsedTimer>

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

QStringList DBManager::parser(QString &line, const char delim)
{
	QStringList list;
	bool inString = false;
	auto marker = line.begin();
	for (auto itr = marker; itr != line.end(); itr++) {
		if (*itr == '"' && !inString) {
			inString = !inString;
			marker += 1;
		} else if (*itr == '"' && inString) {
			list.push_back(QString(marker, itr - marker));
			marker = itr + 2;
			itr = marker - 1;
			inString = !inString;
		} else if (*itr == delim && !inString) {
			list.push_back(QString(marker, itr - marker));
			marker = itr + 1;
		}
	}
	list.push_back(QString(marker));
	return list;
}

void DBManager::ImportTeams()
{
	QString filter = "CSV file (*.csv)";
	QStringList teams;
	// opens system file directory in your home path
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), filter);

	if (fileName.isEmpty()) {
		qDebug() << "No file name specified";
		return;
	}
	// needed to iterate through file...similar to fstream
	QFile file(fileName);
	// populates cities with all the cities in the DB
	GetTeams(teams);

	QElapsedTimer timer;
	timer.start();
	if (!file.open(QFile::ReadOnly)) {
		qDebug() << "DBManager::ImportTeams() : error opening the file(0)";
	} else {
		qDebug() << "file opened";
		QTextStream ss(&file);
		QStringList list;
		bool infoStarted = false;
		bool distanceStarted = false;
		bool souvenirStarted = false;

		while (!ss.atEnd()) {
			QString line = ss.readLine();
			if (line == "//information") {
				infoStarted = true;
				distanceStarted = false;
				souvenirStarted = false;
				line = ss.readLine();
			} else if (line == "//distances") {
				distanceStarted = true;
				infoStarted = false;
				souvenirStarted = false;
				line = ss.readLine();
			} else if (line == "//souvenirs") {
				souvenirStarted = true;
				infoStarted = false;
				distanceStarted = false;
				line = ss.readLine();
			}

			// parse each line in teh csv into a QStringList
			list = parser(line, ',');

			// only insert if the city is unique
			if (!teams.contains(list[0])) {
				query.prepare("INSERT INTO teams(teamNames) VALUES(:team)");
				query.bindValue(":team", list[0]);
				if (!query.exec()) {
					qDebug() << "DBManager::ImportTeams() : error executing query(1)";
					exit(1);
				}
				// re-populates cities with updated city list
				teams.clear();
				GetTeams(teams);
			}

			// finds and stores the id associated with the city name
			query.prepare("SELECT id FROM teams WHERE teamNames = :team");
			query.bindValue(":team", list[0]);
			if (!query.exec()) {
				qDebug() << "DBManager::ImportTeams() : error executing query(2)";
				exit(2);
			}
			query.first();
			int id = query.value(0).toInt();

			if (infoStarted) {
				query.prepare("INSERT INTO information(id, stadiumName,"
							  "seatCap, location, conference, division,"
							  "surfaceType, roofType, dateOpen) VALUES(:id,"
							  ":stadiumName, :seatCap, :location, :conference,"
							  ":division, :surfaceType, :roofType, :dateOpen)");
				query.bindValue(":id", id);
				query.bindValue(":stadiumName", list[1]);
				query.bindValue(":seatCap", list[2]);
				query.bindValue(":location", list[3]);
				query.bindValue(":conference", list[4]);
				query.bindValue(":division", list[5]);
				query.bindValue(":surfaceType", list[6]);
				query.bindValue(":roofType", list[7]);
				query.bindValue(":dateOpen", list[8]);
			} else if (distanceStarted) {
				query.prepare("INSERT INTO distance(id, beginStadium, "
							  "endStadium, distanceTo) VALUES(:id, "
							  ":beginStadium, :endStadium, :distanceTo)");
				query.bindValue(":id", id);
				query.bindValue(":beginStadium", list[1]);
				query.bindValue(":endStadium", list[2]);
				query.bindValue(":distanceTo", list[3]);
			} else if (souvenirStarted) {
				query.prepare("INSERT INTO souvenir(id, items, price) "
							  "VALUES(:id, :items, :price)");
				query.bindValue(":id", id);
				query.bindValue(":items", list[1]);
				query.bindValue(":price", list[2]);
			}

			// If query does not execute, print error
			if (!query.exec()) {
				qDebug() << "DBManager::ImportTeams() : error executing query(3)";
				exit(3);
			}
		}
		query.finish();
	}
	qDebug() << "Elapse time: " << timer.elapsed() << "ms";
}

void DBManager::GetTeams(QStringList &teams)
{
	query.prepare("SELECT teamNames FROM teams");
	if (query.exec()) {
		while (query.next())
			teams.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "DBManager::GetTeams(QStringList &teams) : query failed";
	}
}

void DBManager::GetSouvenirs(QString teamName, QStringList &list)
{
	query.prepare("SELECT items FROM souvenir, teams WHERE teamNames = :teamName AND teams.id = souvenir.id");
	query.bindValue(":teamName", teamName);

	if (query.exec()) {
		while (query.next())
			list.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "DBManager::GetSouvenirs(QString teamName, QStringList &list) : query failed";
	}
}

int DBManager::GetNumSouvenir(QString teamName)
{

	query.prepare("SELECT COUNT(*) FROM souvenir, teams WHERE teamNames = "
				  ":teamName AND teams.id = souvenir.id");
	query.bindValue(":teamName", teamName);

	if (query.exec()) {
		query.first();
		return query.value(0).toInt();
	}
	qDebug() << "DBManager::GetNumSouvenir(QString teamName) : query failed";
	return -1;
}

int DBManager::GetNumTeams()
{
	query.prepare("SELECT COUNT(*) teams");
	if (query.exec()) {
		query.first();
		return query.value(0).toInt();
	}
	qDebug() << "DBManager::GetNumTeams() : query failed";
	return -1;
}

QString DBManager::SouvenirNameToPrice(QString team, QString souvenir)
{
	query.prepare("SELECT price FROM souvenir, teams WHERE teamNames = :team "
				  "AND teams.id = souvenir.id AND souvenir.items = :souvenir");

	query.bindValue(":team", team);
	query.bindValue(":souvenir", souvenir);

	if (query.exec()) {
		query.first();
		return query.value(0).toString();
	} else { // If query does not execute, print error
		qDebug() << "DBManager::SouvenirNameToPrice(QString team, QString souvenir) : query failed";
	}
	return QString("Error");
}
