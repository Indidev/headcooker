#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QFile>

#include "database/Database.h"

#include <iostream>

using std::cout;
using std::endl;

class Options
{
public:
    static QString style(QString elementName, QString styleName = Instance()->curStyle);
private:
    Options();

    QString curStyle;
    static Options *instance;

    static Options *Instance();
};

#endif // OPTIONS_H
