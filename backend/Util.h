#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QRegExp>
#include <QList>
#include <QStringList>

class Util {
public:

    static int getBodyMargin(QString &style);
    static QString extractCSSTag_S(QString &style, QString className, QString element);
    static int extractCSSTag_I(QString &style, QString className, QString element);
};

#endif // UTIL_H
