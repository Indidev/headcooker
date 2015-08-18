#include "RecipeApiParser.h"

#include <QString>
#include <QList>
#include <QRegExp>

RecipeApiParser::RecipeApiParser()
{
}

XMLTree RecipeApiParser::parseRecipe(const QString xml)
{
    QString tmpXml(xml.trimmed());
    unEscapeXML(tmpXml);

    XMLTree tree;
    tree.addChilds(parse(tmpXml));

    return tree;
}

QList<XMLTreeObject> RecipeApiParser::parse(QString &xml)
{
    xml = xml.trimmed();
    QList<XMLTreeObject> elements;

    if (xml[0].toAscii() == '{') {
        //remove leading '{'
        xml.remove(0, 1);

        while (!xml.isEmpty() && xml[0].toAscii() != '}') {
            switch (xml[0].toAscii()) {
                case '"':
                    elements.append(parseSingle(xml));
                    break;
                case ' ':
                case ',':
                    xml.remove(0, 1);
                    break;
            }
        }
        //remove trailing '}'
        xml.remove(0, 1);
    }
    return elements;
}

XMLTreeObject RecipeApiParser::parseSingle(QString &xml) {
    xml = xml.trimmed();

    if (xml[0].toAscii() == '"') {
        XMLTreeObject element(getString(xml));

        //remove everything up to the next :
        xml.remove(0, xml.indexOf(':') + 1);
        xml = xml.trimmed();

        switch(xml[0].toAscii()) {
            case '{':
                element.addChilds(parse(xml));
                break;
            case '[':
                parseArray(xml, element);
                break;
            case '"':
                element.addValue(getString(xml));
                break;
            default:
                element.addValue(stringToLimiter(xml));
        }
        return element;
    }

    //return empty tree object
    return XMLTreeObject("");
}

void RecipeApiParser::parseArray(QString &xml, XMLTreeObject &element) {
    xml = xml.trimmed();

    if (xml[0].toAscii() == '[') {

        //remove leading '['
        xml.remove(0, 1);
        while(!xml.isEmpty() && xml[0].toAscii() != ']') {
            //remove comma if necessary
            if (xml[0].toAscii() == ',') {
                xml.remove(0, 1);
                xml = xml.trimmed();
            }

            switch(xml[0].toAscii()) {
                case '"':
                    element.addValue(getString(xml));
                    break;
                case '{':
                    XMLTreeObject subElement("");
                    subElement.addChilds(parse(xml));
                    element.addChild(subElement);
                    break;
            }

            xml = xml.trimmed();
        }
        //remove trailing ']'
        xml.remove(0, 1);
    }
}

QString RecipeApiParser::stringToLimiter(QString &xml) {
    QString regstr("[,\\]\}]");
    QRegExp regex(regstr);
    int index = xml.indexOf(regex);
    if (index >= 0){
        QString str = xml.left(index);
        str = str.trimmed();
        xml.remove(0, index);
        return str;
    } else
        return QString::fromStdString("");
}

QString RecipeApiParser::getString(QString &xml) {
    QString str;

    if (xml[0].toAscii() == '"') {
        //remove leading '"'
        xml.remove(0, 1);
        int index = xml.indexOf('"');

        //extract string
        str = xml.left(index);

        //remove string + trailing '"'
        xml.remove(0, index + 1);

    } else {
        printf("abc");
    }
    return str;
}

void RecipeApiParser::unEscapeXML(QString &xml)
{
    xml.replace("\\/", "/", Qt::CaseInsensitive);
    xml.replace("\\r\\n", "\n", Qt::CaseInsensitive);
    xml.replace("\\u00fc", QString::fromUtf8("ü"), Qt::CaseInsensitive);
    xml.replace("\\u00dc", QString::fromUtf8("Ü"), Qt::CaseInsensitive);
    xml.replace("\\u00f6", QString::fromUtf8("ö"), Qt::CaseInsensitive);
    xml.replace("\\u00d6", QString::fromUtf8("Ö"), Qt::CaseInsensitive);
    xml.replace("\\u00e4", QString::fromUtf8("ä"), Qt::CaseInsensitive);
    xml.replace("\\u00c4", QString::fromUtf8("Ä"), Qt::CaseInsensitive);
    xml.replace("\\u00df", QString::fromUtf8("ß"), Qt::CaseInsensitive);
}
