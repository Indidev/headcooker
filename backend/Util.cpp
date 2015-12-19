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

QColor Util::extractCSSTag_C(QString &style, QString className, QString element)
{
    QColor color;
    QString elem = extractCSSTag_S(style, className, element);
    if (elem.startsWith("rgb")) {
        QStringList colors = elem.split(QRegExp("\\D"), QString::SkipEmptyParts);
        if (colors.length() >= 3) {
            color = QColor(colors[0].toInt(), colors[1].toInt(), colors[2].toInt());
            if (colors.length() > 3)
                color.setAlpha(colors[3].toInt());
        }
    } else
        color = QColor(elem);

    return color;
}

QImage Util::getRatingImg(float rating, QString ratingMask, QColor color, QColor bgColor)
{
    QImage ratingImg;

    int spacing = 3;
    QImage maskPart;
    if (maskPart.load(ratingMask)) {
        QImage mask(5 * maskPart.width() + 4 * spacing, maskPart.height(), QImage::Format_ARGB32);
        mask.fill(Qt::black);

        QPainter painter;
        painter.begin(&mask);

        //copy parts
        for (int i = 0; i < 5; i++) {
            painter.drawImage(i * (maskPart.width() + spacing), 0, maskPart);
        }
        painter.end();

        //draw rating
        ratingImg = QImage(mask);

        painter.begin(&ratingImg);

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.fillRect(mask.rect(), Qt::transparent);

        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.fillRect(mask.rect(), bgColor);

        for (int i = 0; i < 5; i++) {
            int offset = i * (maskPart.width() + spacing);
            float percentage = std::min(1.f, std::max(0.f, rating - (float) i));
            QRect rect(offset, 0, percentage * maskPart.width(), mask.height());
            painter.fillRect(rect, color);
        }

        painter.end();

        ratingImg.setAlphaChannel(mask);
    }

    return ratingImg;
}

void Util::unescapeUnicode(QString &str) {
    int index;
    char* tmpStr = (char *) malloc(5 * sizeof(char));

    while ((index = str.indexOf("\\u")) >= 0) {

        int u_1 = str.mid(index + 2, 2).toInt(0, 16);
        int u_2 = str.mid(index + 4, 2).toInt(0, 16);

        int offset = 0;

        //Thanks for this part goes to Jan Düpmeier (https://github.com/jduepmeier)
        if (u_1 == 0x00 && u_2 <= 0x7F) {
            tmpStr[offset] = u_2;
        } else if (u_1 >= 0 && u_1 <= 0x07 && u_2 >= 0x80) {
            tmpStr[offset] = 0xC0;
            tmpStr[offset] |= (u_1 & 0x07) << 2 | (0xC0 & u_2) >> 6;
            offset++;
            tmpStr[offset] = 0x80;
            tmpStr[offset] |= u_2 & 0x3F;
        } else if (u_1 >= 0x80) {
            tmpStr[offset] = 0xE0;
            tmpStr[offset] |= (u_1 & 0xF0) >> 4;
            offset++;
            tmpStr[offset] = 0x80;
            tmpStr[offset] |= (u_1 & 0x0F) << 2 | (u_2 & 0xC0) >> 6;
            offset++;
            tmpStr[offset] = 0x80;
            tmpStr[offset] |= u_2 & 0x3F;
        }
        tmpStr[offset + 1] = '\0';

        str.replace(index, 6, QString::fromUtf8(tmpStr));
    }
    free(tmpStr);
}
