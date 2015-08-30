#include "Database.h"

Database *Database::instance = NULL;

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

Database &Database::DB()
{
    if (!Database::instance)
        instance = new Database(DB_PATH);

    return *instance;
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

int Database::getUsageID(QString usage) {
    return getSingleItemID("USAGE_INFO", usage);
}

bool Database::hasRecipe(QString onlineID)
{
    QString sql = "SELECT * FROM RECIPE WHERE ONLINE_ID = '" + escape(onlineID) + "';";
    QList<DataRow> row;

    if (!execSQL(sql, &row))
        return false;
    else
        return row.size() > 0;
}

bool Database::hasRecipe(int id) {
    QString sql = "SELECT * FROM RECIPE WHERE ID = " + QString::number(id) + ";";
    QList<DataRow> row;

    if (!execSQL(sql, &row))
        return false;
    else
        return row.size() > 0;
}

bool Database::saveRecipe(const Recipe &recipe) {
    if (hasRecipe(recipe.recipeID)) {
        return updateRecipe(recipe);
    } else {
       return addRecipe(recipe);
    }
}

bool Database::updateRecipe(const Recipe &recipe) {
    //addTags
    bool success = true;
    for (QString tag : recipe.addedTags) {
        QString sql = "INSERT INTO RECIPE_TAGS(TAG_ID, RECIPE_ID)" \
                "VALUES(" + QString::number(getTagID(tag.trimmed())) + "," + QString::number(recipe.databaseID) + ");";
        success = execSQL(sql);

        if (!success)
            break;
    }

    //removeTags

    if (success) {
        for (QString tag : recipe.removedTags) {
            int tagID = getTagID(tag.trimmed());

            QList<DataRow> row;
            QString sql = "DELETE FROM RECIPE_TAGS WHERE " \
                    "TAG_ID = " + QString::number(tagID) + " AND " \
                    "RECIPE_ID = " + QString::number(recipe.databaseID) + ";";
            sql += "SELECT COUNT(ID) AS NUM FROM RECIPE_TAGS WHERE TAG_ID = " + QString::number(tagID) + ";";

            success = execSQL(sql, &row);

            //check if tag can be removed out of the database
            if (success) {
                if (row[0].get("NUM").toInt() == 0) {
                    sql = "DELETE FROM TAG WHERE ID = " + QString::number(tagID) + ";";

                    success = execSQL(sql);
                }
            }
        }
    }
    return success;
}

bool Database::addRecipe(const Recipe &recipe) {
    if (recipe.title.isEmpty())
        return false;

    QString sql = "INSERT INTO RECIPE(ONLINE_ID, TITLE, SUBTITLE, INSTRUCTION, SERVINGS, RATING, IMG_PATH, PREPARATION_TIME, COOKING_TIME, RESTING_TIME, KCAL, DIFFICULTY_ID, USER_ID)" \
            "VALUES(" \
            "'" + escape(recipe.recipeID) + "'," \
            "'" + escape(recipe.title) + "'," \
            "'" + escape(recipe.subtitle) + "'," \
            "'" + escape(recipe.instructions) + "'," \
            "" + QString::number(recipe.servings) + "," \
            "" + QString::number(recipe.rating) + "," \
            "'" + escape(recipe.imagePath) + "'," \
            "" + QString::number(recipe.preparationTime) + "," \
            "" + QString::number(recipe.cookingTime) + "," \
            "" + QString::number(recipe.restingTime) + "," \
            "" + QString::number(recipe.kCalories) + "," \
            "" + QString::number(recipe.difficulty) + "," \
            "" + QString::number(getUserID(escape(recipe.owner))) + "" \
            ");";
    sql += "SELECT ID FROM RECIPE WHERE ONLINE_ID = '" + recipe.recipeID + "';";

    QList<DataRow> row;

    bool success = execSQL(sql, &row) && row[0].get("id").toInt() > 0;
    int id;

    //insert tags
    if (success) {
        id = row[0].get("id").toInt();
        for (QString tag : recipe.tags) {
            QString sql = "INSERT INTO RECIPE_TAGS(TAG_ID, RECIPE_ID)" \
                    "VALUES(" + QString::number(getTagID(tag)) + "," + QString::number(id) + ");";
            success = execSQL(sql);

            if (!success)
                break;
        }
    }

    //insert ingredients
    if (success) {
        for (DataTypes::IngredientList group : recipe.ingredientGroups.groups) {
            int groupID = getIngredientGroupID(group.header);

            for (DataTypes::Ingredient ingredient : group.ingredients) {
                int ingredientID = getIngredientID(ingredient.name);
                int unitID = getUnitID(ingredient.unit);
                int usageID = getUsageID(ingredient.usageInfo);

                QString sql = "INSERT INTO INGREDIENT_LIST(AMOUNT, RECIPE_ID, ING_ID, GROUP_ID, UNIT_ID, USAGE_ID)" \
                        "VALUES(" +
                        QString::number(ingredient.amount) + "," +
                        QString::number(id) + "," +
                        QString::number(ingredientID) + "," +
                        QString::number(groupID) + "," +
                        QString::number(unitID) + "," +
                        QString::number(usageID) + ");";
                success = execSQL(sql);
                if (!success)
                    break;
            }
            if (!success)
                break;
        }
    }

    return success;
}

bool Database::getRecipe(QString id, QList<DataRow> &row) {
    QString sql = "SELECT * FROM RECIPE WHERE ONLINE_ID ='" + id + "' OR ID = " + id +  ";";

    return execSQL(sql, &row);
}

bool Database::getRecipe(int id, QList<DataRow> &row) {
    QString sql = "SELECT * FROM RECIPE WHERE ID =" + QString::number(id) + ";";

    return execSQL(sql, &row);
}

bool Database::listOfRecipes(QList<DataRow> &row) {
    QString sql = "SELECT ID, TITLE FROM RECIPE ORDER BY TITLE ASC;";

    return execSQL(sql, &row);
}

QString Database::getUserName(int id) {
    return getNameFromID("USER", id);
}

QString Database::getDifficulty(int id) {
    if (id > 3 || id < 1)
        return getNameFromID("DIFFICULTY", 0);
    else
        return getNameFromID("DIFFICULTY", id);
}

QString Database::getIngredientName(int id) {
    return getNameFromID("INGREDIENT", id);
}

QString Database::getGroupName(int id) {
    return getNameFromID("INGREDIENT_GROUP", id);
}

QString Database::getUnitName(int id) {
    return getNameFromID("UNIT", id);
}

QString Database::getUsageInfo(int id) {
    return getNameFromID("USAGE_INFO", id);
}

bool Database::recipesContaining(QString needle, QList<DataRow> &rows) {
    QString sql = "SELECT R.* " \
            "FROM RECIPE AS R " \
                "JOIN RECIPE_TAGS as RT ON RT.RECIPE_ID = R.ID " \
                "JOIN TAG ON TAG.ID = RT.TAG_ID " \
                "JOIN INGREDIENT_LIST as IL ON IL.RECIPE_ID = R.ID " \
                "JOIN INGREDIENT as I ON I.ID = IL.ING_ID " \
            "WHERE TAG.NAME LIKE '%" + needle + "%' " \
                "OR I.NAME LIKE '%" + needle + "%' " \
                "OR TITLE LIKE '%" + needle + "%' " \
            "GROUP BY R.ID;";

    return execSQL(sql, &rows);
}

QList<QString> Database::getTags(int recipeID) {
    QString sql = "SELECT NAME " \
            "FROM RECIPE_TAGS " \
            "JOIN TAG " \
            "ON TAG.ID = TAG_ID " \
            "WHERE RECIPE_ID = " + QString::number(recipeID) + ";";

    QList<QString> keys;
    QList<DataRow> rows;

    if (execSQL(sql, &rows)) {
        for (DataRow row : rows) {
            keys.append(row.get("name"));
        }
    }

    return keys;
}

DataTypes::IngredientGroups Database::getIngredients(int recipeID) {
    QString sql = "SELECT " \
                "INGREDIENT_GROUP.NAME AS 'GROUP'," \
                "AMOUNT," \
                "Unit.NAME AS 'UNIT'," \
                "INGREDIENT.NAME AS 'NAME'," \
                "USAGE_INFO.NAME as 'USAGE_INFO' " \
            "FROM INGREDIENT_LIST " \
                "JOIN INGREDIENT " \
                "ON INGREDIENT.ID = ING_ID " \
                "JOIN UNIT " \
                "ON UNIT.ID = UNIT_ID " \
                "JOIN INGREDIENT_GROUP " \
                "ON INGREDIENT_GROUP.ID = GROUP_ID " \
                "JOIN USAGE_INFO " \
                "ON USAGE_INFO.ID = USAGE_ID " \
            "WHERE RECIPE_ID = " + QString::number(recipeID) + ";";
    DataTypes::IngredientGroups ingredients;

    QList<DataRow> rows;

    if (execSQL(sql, &rows)) {
        for (DataRow &row : rows) {
            QString groupName = row.get("group");
            float amount = row.get("amount").toFloat();
            QString unit = row.get("unit");
            QString name = row.get("name");
            QString usage = row.get("usage_info");

            DataTypes::Ingredient ingredient{amount, unit, name, usage};
            ingredients.add(groupName, ingredient);

            //group.append(DataTypes::Ingredient{amount, unit, name, usage});
            /*group.append(DataTypes::Ingredient{
                             row.get("amount").toFloat(),
                             row.get("unit"),
                             row.get("name"),
                             row.get("usage_info")});*/
        }
    }

    return ingredients;
}



QString Database::getNameFromID(QString tablename, int id) {
    QString sql = "SELECT NAME FROM " + tablename + " WHERE ID = " + QString::number(id) + ";";

    QList<DataRow> row;

    if (execSQL(sql, &row) && row.size() > 0)
        return row[0].get("name");
    else
        return "";
}

int Database::getSingleItemID(QString tablename, QString name) {
    QString sql = "SELECT ID FROM " + tablename + " WHERE NAME = '" + escape(name) + "';";

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
            "VALUES('" + escape(name) + "');" \
            "SELECT ID FROM " + tablename.toUpper() + " WHERE NAME = '" + escape(name) + "';";

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
        QString key = QString::fromLocal8Bit(colNames[i]);
        QString value = QString::fromLocal8Bit(values[i]);
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
            "KCAL INTEGER, " \
            "DIFFICULTY_ID INTEGER, "\
            "USER_ID INTEGER NOT NULL, "\
            "FOREIGN KEY(DIFFICULTY_ID) REFERENCES DIFFICULTY(ID)," \
            "FOREIGN KEY(USER_ID) REFERENCES USER(ID) );";

    sql += "CREATE TABLE Ingredient_List(" \
            "ID INTEGER PRIMARY KEY," \
            "Amount INTEGER," \
            "RECIPE_ID INTEGER NOT NULL," \
            "ING_ID INTEGER NOT NULL," \
            "Group_ID INTEGER NOT NULL," \
            "UNIT_ID INTEGER NOT NULL," \
            "USAGE_ID INTEGER NOT NULL," \
            "FOREIGN KEY(RECIPE_ID) REFERENCES RECIPE(ID)," \
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

QString Database::escape(QString input) {
    return input.replace("'", "''");
}


