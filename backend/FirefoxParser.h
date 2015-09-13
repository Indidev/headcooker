#ifndef FIREFOXPARSER_H
#define FIREFOXPARSER_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QList>
#include <QRegExp>

#include <iostream>

using namespace std;

class FirefoxParser
{
public:
    static QList<QString> parse(QString path);
protected:
    FirefoxParser();
    static bool extractNextUrl(QString &json, QString &url);
};

#endif // FIREFOXPARSER_H
