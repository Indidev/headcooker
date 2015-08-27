#ifndef DATAROW_H
#define DATAROW_H

#include <QString>
#include <QList>

class DataRow
{
public:
    DataRow();
    void add(QString key, QString value);
    QString get(QString key);

protected:
    struct Pair {
        QString key;
        QString value;
    };

    QList<Pair> data;
};

#endif // DATAROW_H