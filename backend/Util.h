#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QRegExp>
#include <QList>
#include <QStringList>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QPaintEngine>

//debuging
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Util {
public:

    static int getBodyMargin(QString &style);
    static QString extractCSSTag_S(QString &style, QString className, QString element);
    static int extractCSSTag_I(QString &style, QString className, QString element);
    static QImage getRatingImg(float rating, QString ratingMask, QColor color = QColor(0, 127, 0), QColor bgColor = Qt::lightGray);
    static QColor extractCSSTag_C(QString &style, QString className, QString element);
    static void unescapeUnicode(QString &str);
};

#endif // UTIL_H
