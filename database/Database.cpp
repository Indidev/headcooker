#include "Database.h"

Database::Database(QString databasePath)
{
    this->databasePath = databasePath;
    errMsg = 0;
    bool isInitiated = QFile(databasePath).exists();

    errCode = sqlite3_open(databasePath.toStdString().c_str(), &db);

    if (errCode) {
        cerr << "Could not open database" << endl;

        //TODO should do something else then exit here... this is pretty dirty
        exit(1);
    }

    if (!isInitiated)
        initDB();
}

Database::~Database()
{
    sqlite3_close(db);
}

int Database::getUserID(QString username) {
    return getSingleItemID("USER", username);
}

int Database::getTagID(QString tag) {
    return getSingleItemID("TAG", tag);
}

int Database::getIngredientID(QString ingredientName) {
    return getSingleItemID("INGREDIENT", ingredientName);
}

int Database::getIngredientGroupID(QString groupName) {
    return getSingleItemID("INGREDIENT_GROUP", groupName);
}

int Database::getUnitID(QString unitName) {
    return getSingleItemID("UNIT", unitName);
}

bool Database::hasRecipe(QString onlineID)
{

}

int Database::getSingleItemID(QString tablename, QString name) {
    QString sql = "SELECT ID FROM " + tablename + " WHERE NAME = '" + name + "';";

    QList<DataRow> rows;

    if (!execSQL(sql, &rows))
        return -1;

    if (rows.size() > 0) {
        return rows[0].get("id").toInt();
    } else {
        return insertSingleItem(tablename , name);
    }
}

int Database::insertSingleItem(QString tablename, QString name) {
    QString sql = "INSERT INTO " + tablename.toUpper() + "(NAME)" \
            "VALUES('" + name + "');" \
            "SELECT ID FROM " + tablename.toUpper() + " WHERE NAME = '" + name + "';";

    QList<DataRow> row;

    if (execSQL(sql, &row))
        return row[0].get("id").toInt();
    else
        return -1;
}

bool Database::execSQL(QString sql, QList<DataRow> *rows) {

    errCode = sqlite3_exec(db, sql.toStdString().c_str(), callback, (void* ) rows, &errMsg);
    if (errCode) {
        printErr();
        return 0;
    }

    return 1;
}

int Database::callback(void *data, int argc, char **values, char **colNames){
    QList<DataRow> *rows = (QList<DataRow> *) data;

    DataRow row;
    for (int i = 0; i < argc; i++) {
        QString key = QString::fromLatin1(colNames[i]);
        QString value = QString::fromLatin1(values[i]);
        row.add(key, value);
    }

    rows->append(row);

    return 0;
}

void Database::initDB() {
    QString sql;

    sql += "CREATE TABLE Tag(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE Ingredient(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE Ingredient_Group(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE USAGE_INFO(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE Unit(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE User(" \
            "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE Difficulty(" \
           "ID INTEGER PRIMARY KEY," \
            "NAME TEXT NOT NULL );";

    sql += "CREATE TABLE Recipe(" \
            "ID INTEGER PRIMARY KEY," \
            "ONLINE_ID TEXT NOT NULL, " \
            "TITLE TEXT NOT NULL, " \
            "SUBTITLE TEXT," \
            "INSTRUCTION TEXT NOT NULL, "\
            "SERVINGS FLOAT NOT NULL," \
            "RATING FLOAT NOT NULL," \
            "IMG_PATH Text," \
            "PREPARATION_TIME INTEGER, " \
            "COOKING_TIME INTEGER, "\
            "RESTING_TIME INTEGER, "\
            "DIFFICULTY_ID INTEGER, "\
            "USER_ID INTEGER NOT NULL, "\
            "FOREIGN KEY(DIFFICULTY_ID) REFERENCES DIFFICULTY(ID)," \
            "FOREIGN KEY(USER_ID) REFERENCES USER(ID) );";

    sql += "CREATE TABLE IngredientList(" \
            "ID INTEGER PRIMARY KEY," \
            "Amount INTEGER," \
            "ING_ID INTEGER NOT NULL," \
            "Group_ID INTEGER NOT NULL," \
            "UNIT_ID INTEGER NOT NULL," \
            "USAGE_ID INTEGER NOT NULL," \
            "FOREIGN KEY(Ing_ID) REFERENCES Ingredient(ID)," \
            "FOREIGN KEY(Group_ID) REFERENCES Ingredient_Group(ID)," \
            "FOREIGN KEY(Unit_ID) REFERENCES Unit(ID)," \
            "FOREIGN KEY(Usage_ID) REFERENCES USAGE_INFO(ID) );";

    sql += "CREATE TABLE RECIPE_TAGS(" \
            "ID INTEGER PRIMARY KEY," \
            "TAG_ID INTEGER NOT NULL," \
            "RECIPE_ID INTEGER NOT NULL," \
            "FOREIGN KEY(TAG_ID) REFERENCES TAG(ID)," \
            "FOREIGN KEY(RECIPE_ID) REFERENCES RECIPE(ID) );";

    sql = sql.toUpper();

    sql += "INSERT INTO DIFFICULTY(ID, NAME)" \
            "VALUES(0, 'n/a');" \
            "INSERT INTO DIFFICULTY(ID, NAME)" \
            "VALUES(1, 'simpel');" \
            "INSERT INTO DIFFICULTY(ID, NAME)" \
            "VALUES(2, 'normal');" \
            "INSERT INTO DIFFICULTY(ID, NAME)" \
           "VALUES(3, 'pfiffig');";

    execSQL(sql);
}

void Database::printErr()
{
    cerr << errMsg << endl;
    sqlite3_free(errMsg);
}


