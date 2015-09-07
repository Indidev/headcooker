#include "Options.h"

Options *Options::instance = NULL;

Options::Options()
{
    DataRow row = Database::DB().getOptions();
    curStyle = row.get("CUR_STYLE");
}

Options *Options::Instance()
{
    if (!instance)
        instance = new Options;

    return instance;
}

QString Options::style(QString elementName, QString styleName) {
    QString filepath = "style/";
    if (styleName.isEmpty() || !QFile::exists(filepath + styleName + "/" + elementName + ".css")) {
        filepath += "default";
    } else {
        filepath += styleName;
    }

    filepath += "/" + elementName + ".css";
    cout << filepath.toStdString() << endl;

    QFile styleFile(filepath);
    QString style;

    if (styleFile.exists()) {
        styleFile.open(QFile::ReadOnly);
        style = QString(styleFile.readAll());
        styleFile.close();
    }

    return style;
}
