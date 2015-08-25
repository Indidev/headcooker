#include "Recipe.h"

Recipe::Recipe(QString id)
{
    if (isInDatabase(id)) {
        loadFromDatabase(id);
    } else {
        loadFromURL(id);
    }
}

QString Recipe::getTitle()
{
    return title;
}

QString Recipe::getSubtitle()
{
    return subtitle;
}

QString Recipe::getOwner()
{
    return owner;
}

QString Recipe::getInstructions()
{
    return instructions;
}

QList<QString> Recipe::getKeyWords()
{
    return keyWords;
}

QPixmap Recipe::getImage()
{
    return picture;
}

float Recipe::getServings()
{
    return servings;
}

float Recipe::getRating()
{
    return rating;
}

QList<QPair<QString, QString>> Recipe::getMetaInfo()
{
    QList<QPair<QString, QString>> metaInfo;

    if (preparationTime > 0)
        metaInfo.append(QPair<QString, QString>{"Arbeitszeit: ", getTime(preparationTime)});

    if (cookingTime > 0)
        metaInfo.append(QPair<QString, QString>{"Koch-/Backzeit: ", getTime(cookingTime)});

    if (restingTime > 0)
        metaInfo.append(QPair<QString, QString>{"Ruhezeit: ", getTime(restingTime)});

    {
        QString name = "Schwierigkeitsgrad: ";
        //TODO fetch names from database
        QString value = difficulty == 1?"simpel":difficulty == 2?"normal":difficulty == 3?"schwer":"n/a";
        metaInfo.append(QPair<QString, QString>{name, value});
    }

    {
        QString name = "Kalorien p. P.: ";
        QString value = "";
        if (kCalories > 0)
            value += QString::fromStdString("ca. ") + QString::number(kCalories) + " kcal ";
        else
            value += "keine Angabe ";
        metaInfo.append(QPair<QString, QString>{name, value});
    }

    return metaInfo;
}

QList<QPair<QString, QList<Recipe::Ingredient>>> Recipe::getIngredientGroups()
{
    return ingredientGroups;
}

QString Recipe::getTime(int minutes) {
    int days = minutes / 1440;
    minutes = minutes % 1440;
    int hours = minutes / 60;
    minutes = minutes % 60;

    QString result = "ca. ";

    if (days > 0)
        result += QString::number(days) + (days > 1?" Tage ":" Tag ");
    if (hours > 0)
        result += QString::number(hours) + " Std. ";
    if (minutes > 0)
        result += QString::number(minutes) + " Min. ";

    return result;
}

void Recipe::loadFromDatabase(QString id) {
    (void) id;
    //TODO: impement this
}

void Recipe::loadFromURL(QString id)
{
    //TODO add errorhandling

    //load xml
    Curler curler;

    QString url = API_URL + id;
    QString xml = curler.getQString(url);

    XMLTree xmlData = RecipeApiParser::parseRecipe(xml);

    //load data
    recipeID = xmlData.getChild("id").getValue();
    if (recipeID == id) { //check if xml is valid

        title = xmlData.getChild("title").getValue();
        subtitle = xmlData.getChild("subtitle").getValue();

        //owner
        ownerID = xmlData.getChild("owner").getChild("id").getValue();
        owner = xmlData.getChild("owner").getChild("username").getValue();

        //instructions
        instructions = xmlData.getChild("instructions").getValue();

        //tags
        for (QString tag : xmlData.getChild("tags").getValues()) {
            keyWords.append(tag);
        }

        //image
        hasImage = xmlData.getChild("hasImage").getValue() == "true";
        if (hasImage) {
            QString imageID = xmlData.getChild("previewImageId").getValue();
            fetchImage(imageID, curler);
        }

        //ingredients
        for (XMLTreeObject header : xmlData.getChild("ingredientGroups").getChilds()) {
            QString headerName = header.getChild("header").getValue();
            QList<Ingredient> ingredients;

            for (XMLTreeObject ingredient : header.getChild("ingredients").getChilds()) {
                float a = ingredient.getChild("amount").getValue().toFloat();
                QString u = ingredient.getChild("unit").getValue();
                QString n = ingredient.getChild("name").getValue();
                QString uI = ingredient.getChild("usageInfo").getValue();

                ingredients.push_back(Ingredient{a, u, n, uI});
            }
            ingredientGroups.push_back(QPair<QString, QList<Ingredient>>{headerName, ingredients});
        }

        //Metainfo
        servings = xmlData.getChild("servings").getValue().toFloat();
        rating = xmlData.getChild("rating").getChild("rating").getValue().toFloat();
        preparationTime = xmlData.getChild("preparationTime").getValue().toInt();
        kCalories = xmlData.getChild("kCalories").getValue().toInt();
        cookingTime = xmlData.getChild("cookingTime").getValue().toInt();
        restingTime = xmlData.getChild("restingTime").getValue().toInt();
        difficulty = xmlData.getChild("difficulty").getValue().toInt();
    }

}

void Recipe::fetchImage(QString imageID, Curler &curler){
    picture = QPixmap(420, 280);

    QString url = API_URL;
    url += recipeID;
    url += "/images/";
    url += imageID;

    XMLTree imageXML = RecipeApiParser::parseRecipe(curler.getQString(url));

    QString imageUrl = imageXML.getChild("urls").getChild("crop-420x280").getChild("cdn").getValue();

    picture.loadFromData(curler.getQByteArray(imageUrl), "JPG");
}

bool Recipe::isInDatabase(QString id) {
    (void) id;
    //TODO: remove this if database is implemented
    return false;
}
