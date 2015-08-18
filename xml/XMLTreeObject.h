#ifndef XMLTREEOBJECT_H
#define XMLTREEOBJECT_H

#include <QString>
#include <QList>

class XMLTreeObject {
public:
    XMLTreeObject(QString key);
    QList<QString> getValues();
    QList<XMLTreeObject> getChilds();
    XMLTreeObject getChild(QString key);
    QString getKey();
    QString getFirstValue();
    void addChild(XMLTreeObject child);
    void addChilds(QList<XMLTreeObject> childs);
    void addValue(QString value);
    void addValues(QList<QString> values);

    bool isLeaf();
    bool isEmpty();

protected:
    QString key;
    QList<QString> values;
    QList<XMLTreeObject> childs;

};

#endif // XMLTREEOBJECT_H
