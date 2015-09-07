#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QList>
#include <sqlite3.h>
#include <iostream>

#include "DataRow.h"
#include "../Recipe.h"
#include "../DataTypes.h"

using std::cerr;
using std::endl;

static const QString DB_PATH = "test.db";

class Recipe;
struct Ingredient;

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
    bool getRecipe(QString id, QList<DataRow> &row);
    bool getRecipe(int id, QList<DataRow> &row);
    DataRow getOptions();
    bool saveOptions(DataRow);

    QString getNameFromID(QString tablename, int id);
    QString getDifficulty(int id);
    QString getUserName(int id);
    QString getIngredientName(int id);
    QString getGroupName(int id);
    QString getUnitName(int id);
    QList<QString> getTags(int recipeID);
    QString getUsageInfo(int id);
    DataTypes::IngredientGroups getIngredients(int recipeID);
    bool listOfRecipes(QList<DataRow> &row);
    bool recipesContaining(QString needle, QList<DataRow> &rows);
    bool deleteRecipe(const Recipe &recipe);
    bool deleteRecipe(int id);
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
    QString escape(QString input);
};

#endif // DATABASE_H
