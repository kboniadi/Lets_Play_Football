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
#include <QTime>

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

    void getTeams(QStringList& teams);

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
};


#endif // DBMANAGER_H
