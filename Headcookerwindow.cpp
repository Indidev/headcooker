#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    QString id("2138001343651445");


    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/1235651228459595");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/814121185712740");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/197551083658477");

    ui->centralWidget->layout()->addWidget(new RecipeWidget(id));
    testDB();
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}

void HeadcookerWindow::testDB() {
    sqlite3 *db;
       char *zErrMsg = 0;
       int  rc;
       QString sql("");

       /* Open database */
       rc = sqlite3_open("test.db", &db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          exit(0);
       }else{
          fprintf(stdout, "Opened database successfully\n");
       }

       sql += "CREATE TABLE Tag(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE Ingredient(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE Ingredient_Group(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE USAGE_INFO(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE Unit(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE User(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "ONLINE_ID TEXT NOT NULL, " \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE Difficulty(" \
              "ID INT PRIMARY KEY NOT NULL," \
               "NAME TEXT NOT NULL );";

       sql += "CREATE TABLE Recipe(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "ONLINE_ID TEXT NOT NULL, " \
               "TITLE TEXT NOT NULL, " \
               "SUBTITLE TEXT," \
               "INSTRUCTION TEXT NOT NULL, "\
               "SERVINGS FLOAT NOT NULL," \
               "RATING FLOAT NOT NULL," \
               "IMG_PATH Text," \
               "PREPARATION_TIME INT, " \
               "COOKING_TIME INT, "\
               "RESTING_TIME INT, "\
               "DIFFICULTY_ID INT, "\
               "USER_ID INT NOT NULL, "\
               "FOREIGN KEY(DIFFICULTY_ID) REFERENCES DIFFICULTY(ID)," \
               "FOREIGN KEY(USER_ID) REFERENCES USER(ID) );";

       sql += "CREATE TABLE IngredientList(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "Amount INT," \
               "ING_ID INT NOT NULL," \
               "Group_ID INT NOT NULL," \
               "UNIT_ID INT NOT NULL," \
               "USAGE_ID INT NOT NULL," \
               "FOREIGN KEY(Ing_ID) REFERENCES Ingredient(ID)," \
               "FOREIGN KEY(Group_ID) REFERENCES Ingredient_Group(ID)," \
               "FOREIGN KEY(Unit_ID) REFERENCES Unit(ID)," \
               "FOREIGN KEY(Usage_ID) REFERENCES USAGE_INFO(ID) );";

       sql += "CREATE TABLE RECIPE_TAGS(" \
               "ID INT PRIMARY KEY NOT NULL," \
               "TAG_ID INT NOT NULL," \
               "RECIPE_ID INT NOT NULL," \
               "FOREIGN KEY(TAG_ID) REFERENCES TAG(ID)," \
               "FOREIGN KEY(RECIPE_ID) REFERENCES RECIPE(ID) );";

       sql = sql.toUpper();

       /* Create SQL statement */
       /*sql = "CREATE TABLE COMPANY("  \
             "ID INT PRIMARY KEY     NOT NULL," \
             "NAME           TEXT    NOT NULL," \
             "AGE            INT     NOT NULL," \
             "ADDRESS        CHAR(50)," \
             "SALARY         REAL );"\
             "CREATE TABLE COMPANY2("  \
                          "ID INT PRIMARY KEY     NOT NULL," \
                          "NAME           TEXT    NOT NULL," \
                          "AGE            INT     NOT NULL," \
                          "ADDRESS        CHAR(50)," \
                          "SALARY         REAL );";*/

       /* Execute SQL statement */
       rc = sqlite3_exec(db, sql.toStdString().c_str(), NULL, 0, &zErrMsg);
       if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       }else{
          fprintf(stdout, "Table created successfully\n");
       }
       sqlite3_close(db);
}
