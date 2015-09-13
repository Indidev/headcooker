#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>

#include "database/Database.h"

#include <iostream>

using std::cout;
using std::endl;

class Options: public QObject
{
    Q_OBJECT
public:
    static QString style(QString elementName, QString styleName = Instance()->curStyle);
    static QStringList styles();
    static QString getCurStyle();
    static void setCurStyle(QString styleName);
    static Options *ptr();
    static void up();
private:
    explicit Options(QObject* parent = 0);

    QString curStyle;
    static Options *instance;

    static Options *Instance();
    void Updated();

signals:
    void updated();
};

#endif // OPTIONS_H
