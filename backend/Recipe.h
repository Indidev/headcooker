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
    Recipe(QString id);
    Recipe(int id);
    ~Recipe();

    QString getTitle();
    QString getSubtitle();
    QString getOwner();
    QString getInstructions();
    QList<QString> getTags();

    QPixmap getImage();

    float getServings();
    float getRating();

    QList<QPair<QString, QString>> getMetaInfo();
    DataTypes::IngredientGroups getIngredientGroups();

    bool save();
    bool hasTag(QString tagname);
    bool addTag(QString tagname);
protected:

    bool hasImage;

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

    QPixmap picture;


    bool isInDatabase(QString id);
    bool isInDatabase(int id);
    void loadFromDatabase(QString id);
    void loadFromDatabase(int id);
    void loadFromDatabase(DataRow &row);
    void loadFromURL(QString id);
    void fetchImage(QString imageID, Curler &curler);
    QString getTime(int minutes);
    void maskImage();
};

#endif // RECIPE_H