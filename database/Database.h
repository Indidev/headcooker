#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QList>
#include <sqlite3.h>
#include <iostream>

#include "DataRow.h"

using std::cerr;
using std::endl;

class Database
{
public:
    Database(QString databasePath);
    ~Database();

    int getUserID(QString username);
    int getTagID(QString tag);
    int getIngredientID(QString ingredientName);
    int getIngredientGroupID(QString groupName);
    int getUnitID(QString unitName);
    bool hasRecipe(QString onlineID);

protected:
    sqlite3 *db;
    char* errMsg;
    int errCode;

    QString databasePath;
    static int callback(void *data, int argc, char **values, char **colNames);
    void initDB();
    void printErr();
    int insertSingleItem(QString tablename, QString name);
    int getSingleItemID(QString tablename, QString name);
    bool execSQL(QString sql, QList<DataRow> *rows = NULL);
};

#endif // DATABASE_H
