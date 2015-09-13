#include "Options.h"

static const QString STYLE_DIR = "style/";
Options *Options::instance = NULL;

Options::Options(QObject* parent) : QObject(parent)
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

void Options::Updated()
{
    emit updated();
}

QString Options::style(QString elementName, QString styleName) {
    QString filepath = STYLE_DIR;
    if (styleName.isEmpty() || !QFile::exists(filepath + styleName + "/" + elementName + ".css")) {
        filepath += "default";
    } else {
        filepath += styleName;
    }

    filepath += "/" + elementName + ".css";
    //cout << filepath.toStdString() << endl;

    QFile styleFile(filepath);
    QString style;

    if (styleFile.exists()) {
        styleFile.open(QFile::ReadOnly);
        style = QString(styleFile.readAll());
        styleFile.close();
    }

    return style;
}

QStringList Options::styles() {
    QDir styleDir(STYLE_DIR);

    if (styleDir.exists())
        return styleDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    else
        return QStringList();
}

QString Options::getCurStyle() {
    return Instance()->curStyle;
}

void Options::setCurStyle(QString styleName) {
    Instance()->curStyle = styleName;

    Database::DB().updateOption("CUR_STYLE", styleName);
    Instance()->Updated();
}

Options *Options::ptr()
{
    return Instance();
}

void Options::up()
{
    Instance()->Updated();
}
