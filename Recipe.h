#ifndef RECIPE_H
#define RECIPE_H

//QT Headers
#include <QString>
#include <QList>
#include <QPair>
#include <QPixmap>

//HeadCooker Headers
#include "Curler.h"
#include "RecipeApiParser.h"

static const QString API_URL = "http://api.chefkoch.de/v2/recipes/";

class Recipe
{
public:

    struct Ingredient {
        float amount;
        QString unit;
        QString name;
        QString usageInfo;
    };

    Recipe(QString id);

    QString getTitle();
    QString getSubtitle();
    QString getOwner();
    QString getInstructions();
    QList<QString> getKeyWords();

    QPixmap getImage();

    float getServings();
    float getRating();

    QList<QPair<QString, QString>> getMetaInfo();
    QList<QPair<QString, QList<Ingredient>>> getIngredientGroups();


protected:

    float rating;
    float servings;

    bool hasImage;

    QString recipeID;
    QString ownerID;
    QString owner;
    QString title;
    QString subtitle;
    QString instructions;

    QList<QString> keyWords;

    //metainfo
    int preparationTime;
    int kCalories;
    int cookingTime;
    int restingTime;
    int difficulty;

    QList<QPair<QString, QList<Ingredient>>> ingredientGroups;

    QPixmap picture;


    bool isInDatabase(QString id);
    void loadFromDatabase(QString id);
    void loadFromURL(QString id);
    void fetchImage(QString imageID, Curler &curler);
    QString getTime(int minutes);
};

#endif // RECIPE_H
