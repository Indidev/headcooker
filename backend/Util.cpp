#include "Util.h"


int Util::getBodyMargin(QString &style)
{
    int startOfBody = style.indexOf("#body");
    if (startOfBody >= 0) {
        int endOfBody = style.indexOf("}", startOfBody);
        int startOfMargin = style.indexOf("margin", startOfBody);
        if (startOfMargin > 0 && startOfMargin > startOfBody) {
            int endOfMargin = style.indexOf(";", startOfMargin);

            if (endOfMargin < 0 || endOfMargin > endOfBody)
                endOfMargin = endOfBody - 1;

            int delta = endOfMargin - startOfMargin + 1;
            QString margin = style.mid(startOfMargin, delta);
            style.remove(startOfMargin, delta);

            return margin.remove(QRegExp("\\D")).toInt();
        }
    }
    return 0;
}
