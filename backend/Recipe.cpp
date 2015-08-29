#include "Recipe.h"

Recipe::Recipe(QString id)
{
    picture = QPixmap(420, 280);
    if (isInDatabase(id)) {
        loadFromDatabase(id);
    } else {
        loadFromURL(id);
    }
}

Recipe::Recipe(int id)
{
    picture = QPixmap(420, 280);
    if (isInDatabase(id))
        loadFromDatabase(id);
}

Recipe::~Recipe()
{
    save();
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

QList<QString> Recipe::getTags()
{
    return tags;
}

QPixmap Recipe::getImage()
{
    return picture;
}

void Recipe::maskImage() {
    QBitmap mask(420, 280);
    mask.load("img/image_mask.png", "png");
    picture.setMask(mask);
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
        metaInfo.append(QPair<QString, QString>{"Schwierigkeitsgrad: ", difficultyStr});
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

DataTypes::IngredientGroups Recipe::getIngredientGroups()
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
    QList<DataRow> row;
    if (Database::DB().getRecipe(id, row))
        loadFromDatabase(row[0]);
}

void Recipe::loadFromDatabase(int id) {
    QList<DataRow> row;
    if (Database::DB().getRecipe(id, row))
        loadFromDatabase(row[0]);
}

void Recipe::loadFromDatabase(DataRow &row) {
    databaseID = row.get("id").toInt();
    recipeID = row.get("online_id");
    title = row.get("title");
    subtitle = row.get("subtitle");
    imagePath = row.get("img_path");
    hasImage = !imagePath.isEmpty();
    instructions = row.get("instruction");
    preparationTime = row.get("preparation_time").toInt();
    cookingTime = row.get("cooking_time").toInt();
    restingTime = row.get("resting_time").toInt();
    difficulty = row.get("difficulty_id").toFloat();
    rating = row.get("rating").toFloat();
    kCalories = row.get("kcal").toInt();
    owner = Database::DB().getUserName(row.get("owner_id").toInt());

    //load keywords
    tags = Database::DB().getTags(databaseID);

    //load ingredients
    ingredientGroups = Database::DB().getIngredients(databaseID);

    if(hasImage)
        hasImage = picture.load(imagePath);

    difficultyStr = Database::DB().getDifficulty(difficulty);

    maskImage();
}

void Recipe::loadFromURL(QString id)
{
    //TODO add errorhandling

    databaseID = -1;
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
            tags.append(tag);
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
            QList<DataTypes::Ingredient> ingredients;

            for (XMLTreeObject ingredient : header.getChild("ingredients").getChilds()) {
                float a = ingredient.getChild("amount").getValue().toFloat();
                QString u = ingredient.getChild("unit").getValue();
                QString n = ingredient.getChild("name").getValue();
                QString uI = ingredient.getChild("usageInfo").getValue();

                ingredients.push_back(DataTypes::Ingredient{a, u, n, uI});
            }
            ingredientGroups.add(headerName, ingredients);
        }

        //Metainfo
        servings = xmlData.getChild("servings").getValue().toFloat();
        rating = xmlData.getChild("rating").getChild("rating").getValue().toFloat();
        preparationTime = xmlData.getChild("preparationTime").getValue().toInt();
        kCalories = xmlData.getChild("kCalories").getValue().toInt();
        cookingTime = xmlData.getChild("cookingTime").getValue().toInt();
        restingTime = xmlData.getChild("restingTime").getValue().toInt();
        difficulty = xmlData.getChild("difficulty").getValue().toInt();
        difficultyStr = Database::DB().getDifficulty(difficulty);

        maskImage();
    }

}

void Recipe::fetchImage(QString imageID, Curler &curler){

    QString url = API_URL;
    url += recipeID;
    url += "/images/";
    url += imageID;

    XMLTree imageXML = RecipeApiParser::parseRecipe(curler.getQString(url));

    QString imageUrl = imageXML.getChild("urls").getChild("crop-420x280").getChild("cdn").getValue();

    picture.loadFromData(curler.getQByteArray(imageUrl), "JPG");
}

bool Recipe::isInDatabase(QString id) {
    return Database::DB().hasRecipe(id);
}

bool Recipe::isInDatabase(int id) {
    return Database::DB().hasRecipe(id);
}

bool Recipe::hasTag(QString tagname) {
    return tags.contains(tagname) || addedTags.contains(tagname);
}

bool Recipe::addTag(QString tagname) {
    if (hasTag(tagname.trimmed()))
        return false;
    addedTags.push_back(tagname.trimmed());
    return true;
}

bool Recipe::save() {
    Database &db = Database::DB();

    if (recipeID > 0 && hasImage) {
        imagePath = "img/recipe/" + recipeID + ".jpg";
        picture.save(imagePath, "jpg");
    }

    return db.saveRecipe(*this);
}