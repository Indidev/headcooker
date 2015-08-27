#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QList>
#include <sqlite3.h>
#include <iostream>

#include "DataRow.h"
#include "../Recipe.h"

using std::cerr;
using std::endl;

static const QString DB_PATH = "test.db";

class Recipe;

class Database
{
public:
    static Database &DB();

    int getUserID(QString username);
    int getTagID(QString tag);
    int getIngredientID(QString ingredientName);
    int getIngredientGroupID(QString groupName);
    int getUnitID(QString unitName);
    int getUsageID(QString usage);
    bool hasRecipe(QString onlineID);
    bool hasRecipe(int id);
    bool saveRecipe(const Recipe &recipe);
protected:
    Database(QString databasePath);
    ~Database();

    static Database *instance;

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
    bool updateRecipe(const Recipe &recipe);
    bool addRecipe(const Recipe &recipe);
};

#endif // DATABASE_H
