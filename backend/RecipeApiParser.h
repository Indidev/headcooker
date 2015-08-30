#ifndef RECIPEAPIPARSER_H
#define RECIPEAPIPARSER_H

#include "xml/XMLTree.h"

#include <QString>

class RecipeApiParser
{
public:
    RecipeApiParser();

    static XMLTree parseRecipe(const QString xml);

protected:
    static QString getString(QString &xml);

    static QList<XMLTreeObject> parse(QString &xml);

    static void unEscapeXML(QString& xml);

    static XMLTreeObject parseSingle(QString &xml);

    static void parseArray(QString &xml, XMLTreeObject &element);

    static QString stringToLimiter(QString &xml);
    int indexOf(QString &xml, QChar needle, int from = 0, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    static QString escape(QString xml);
};

#endif // RECIPEAPIPARSER_H
