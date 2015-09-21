#ifndef RECIPE_H
#define RECIPE_H

//QT Headers
#include <QString>
#include <QList>
#include <QPair>
#include <QPixmap>
#include <QBitmap>

//HeadCooker Headers
#include "Curler.h"
#include "RecipeApiParser.h"
#include "database/Database.h"
#include "DataTypes.h"

static const QString API_URL = "http://api.chefkoch.de/v2/recipes/";
class Database;

class Recipe
{
    friend class Database;
public:
    Recipe(QString id, bool isDummy = false);
    Recipe(int id);
    ~Recipe();

    QString getTitle();
    QString getSubtitle();
    QString getOwner();
    QString getInstructions();
    QList<QString> getTags();

    QImage getImage(QString mask = "");

    float getServings();
    float getRating();

    QList<QPair<QString, QString>> getMetaInfo();
    DataTypes::IngredientGroups getIngredientGroups();

    bool save();
    bool hasTag(QString tagname);
    bool addTag(QString tagname);
    bool removeTag(QString tagname);
protected:

    bool hasImage;
    bool isDummy;

    int databaseID;
    QString recipeID;
    QString ownerID;
    QString owner;
    QString title;
    QString subtitle;
    QString instructions;
    QString imagePath;

    QList<QString> tags;
    QList<QString> addedTags;
    QList<QString> removedTags;

    //metainfo    
    float rating;
    float servings;

    int preparationTime;
    int kCalories;
    int cookingTime;
    int restingTime;
    int difficulty;
    QString difficultyStr;

    DataTypes::IngredientGroups ingredientGroups;

    QImage picture;
    QString curMaskPath;
    QImage maskImage;


    bool isInDatabase(QString id);
    bool isInDatabase(int id);
    void loadFromDatabase(QString id);
    void loadFromDatabase(int id);
    void loadFromDatabase(DataRow &row);
    void loadFromURL(QString id);
    void fetchImage(QString imageID, Curler &curler);
    QString getTime(int minutes);
    void init();
};

#endif // RECIPE_H
