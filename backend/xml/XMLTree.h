#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include <QString>
#include <QList>

#include "XMLTreeObject.h"

class XMLTree
{
public:
    QList<XMLTreeObject> getChilds() {return childs;}
    XMLTreeObject getChild(QString key) {
        for (XMLTreeObject child : childs) {
            if (child.getKey() == key)
                return child;
        }

        //return empty tree object if not present
        return XMLTreeObject("");
    }

    void addChild(XMLTreeObject child) {
        childs.append(child);
    }

    void addChilds(QList<XMLTreeObject> childs) {
        this->childs.append(childs);
    }

protected:
    QList<XMLTreeObject> childs;
};

#endif // XMLOBJECT_H
