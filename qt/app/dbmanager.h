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
#include <bfsNamespace.h> // used to access node struct which is used in bfs class

struct Souvenir
{
    QString name;
    double price;
    Souvenir(QString name,double price):name(name),price(price){}
};



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

	void GetSouvenirs(QString teamName, QStringList &list);

	int GetNumSouvenir(QString teamName);

	int GetNumTeams();

	QString SouvenirNameToPrice(QString team, QString souvenir);

	void AddInfo(QString teamName, QString stadiumName, QString seatCap,
				 QString location, QString conference, QString division,
				 QString surfaceType, QString roofType, QString dateOpen);

	void AddSouvenir(QString teamName, QString item, QString price);
	void UpdateSouvenirPrice(QString teamName, QString item, QString price);
	void DeleteSouvenir(QString teamName, QString item);
	void UpdateInformation(int id, QString stadiumName, QString cap,
						   QString loc, QString surfaceType, QString roofType,
						   QString dateOpen);
	bool isTeamExist(QString teamName);
	bool isSouvenirExist(QString teamName, QString item);
	void addPurchases(int id, QString item, int qty);
	QSqlQuery* getQuery() { return &query; }

    /*!
     * @brief function gets all adjacent cities and distances based on the vertex input and
     * returns it all as a vector of type node
     *
     * @param vertex; reperesents team id
     * @return vector<node>; which contains all the adj teams and their weights
     */
    std::vector<generalContainer::node> getAdjList(int vertex);

    /*!
     * @brief function takes in an id and returns the team name which corresponds with that id
     * @param id; int that represents the teams id
     * @return QString; the name of the team based on the team
     */
    QString getTeamName(int id);
    static bool comparater(generalContainer::node n1, generalContainer::node n2);
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
