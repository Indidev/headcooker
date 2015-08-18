#include "XMLTreeObject.h"


XMLTreeObject::XMLTreeObject(QString key)
{
    this->key = key;
}

bool XMLTreeObject::isLeaf()
{
    return childs.length() == 0;
}

QList<QString> XMLTreeObject::getValues()
{
    return values;
}

QList<XMLTreeObject> XMLTreeObject::getChilds()
{
    return childs;
}

XMLTreeObject XMLTreeObject::getChild(QString key)
{
    for (XMLTreeObject child : childs) {
        if (child.getKey() == key)
            return child;
    }

    //return empty object if key is not present
    return XMLTreeObject("");
}

QString XMLTreeObject::getKey()
{
    return key;
}

QString XMLTreeObject::getFirstValue()
{
    if (values.size() > 0) {
        return values[0];
    } else {
        return QString("");
    }
}

void XMLTreeObject::addChild(XMLTreeObject child)
{
    childs.append(child);
}

void XMLTreeObject::addChilds(QList<XMLTreeObject> childs)
{
    this->childs.append(childs);
}

void XMLTreeObject::addValue(QString value)
{
    values.append(value);
}

void XMLTreeObject::addValues(QList<QString> values)
{
    this->values.append(values);
}

bool XMLTreeObject::isEmpty()
{
    return values.length() == 0 && childs.length() == 0;
}
