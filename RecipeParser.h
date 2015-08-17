#ifndef RECIPEPARSER_H
#define RECIPEPARSER_H

#include <QString>
#include <QList>

class RecipeParser
{
public:
    RecipeParser();

    QString getRecipeName(const QString html);

    QString getInstructions(const QString html);

    struct Ingredient {
        QString amount;
        QString name;
    };

    QList<Ingredient> getIngrediants(const QString html);
    QString removeLink(const QString input);
    QList<QString> getTags(const QString html);
    bool hasError(const QString html);
    QList<QString> getImageLinks(const QString html);
    int getNumPortions(const QString html);
private:
    QString replaceMutations(const QString input);
    QString getBetween(const QString input, QString start, QString end);
};

#endif // RECIPEPARSER_H
