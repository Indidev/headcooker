#include "FirefoxParser.h"

FirefoxParser::FirefoxParser()
{
}

QList<QString> FirefoxParser::parse(QString path)
{
    QList<QString> urlList;
    QString tmpUrl;
    QFile file(path);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QString json = QString(file.readAll());

        while (extractNextUrl(json, tmpUrl)) {
            if (tmpUrl.contains("chefkoch.de") && tmpUrl.split(QRegExp("\\D"), QString::SkipEmptyParts).size() > 0) {
                QStringList splitted = tmpUrl.split(QRegExp("\\D"), QString::SkipEmptyParts);
                if (splitted.size() > 0)
                urlList.append(splitted[0]);
            }
        }
    }
    return urlList;
}

bool FirefoxParser::extractNextUrl(QString &json, QString &url) {
    QString needle = "uri\":\"";
    int index = json.indexOf(needle);
    if (index >= 0) {
        index += needle.length();
        json.remove(0, index);
        index = json.indexOf("\"");
        url = json.left(index);
        json.remove(0, index);
        return true;
    }
    return false;
}
