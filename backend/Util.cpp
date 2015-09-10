#include "Util.h"


QString Util::extractCSSTag_S(QString &style, QString className, QString element)
{
    int startOfClass = style.indexOf("#" + className);
    if (startOfClass >= 0) {
        int endOfClass = style.indexOf("}", startOfClass);
        int startOfElement = style.indexOf(element, startOfClass);
        if (startOfElement > 0 && startOfElement > startOfClass) {
            int endOfElement = style.indexOf(";", startOfElement);

            if (endOfElement < 0 || endOfElement > endOfClass)
                endOfElement = endOfClass - 1;

            int delta = endOfElement - startOfElement + 1;
            QString line = style.mid(startOfElement, delta);
            style.remove(startOfElement, delta);

            QString value = line.left(line.length() - 1).split(":").last().trimmed();
            return value;
        }
    }
    return "";
}

int Util::extractCSSTag_I(QString &style, QString className, QString element)
{
    return extractCSSTag_S(style, className, element).remove(QRegExp("\\D")).toInt();
}
