#include "DataRow.h"

DataRow::DataRow()
{
}

void DataRow::add(QString key, QString value)
{
    data.push_back(Pair{key, value});
}

void DataRow::add(QString key, int value)
{
    data.push_back(Pair{key, QString::number(value)});
}

void DataRow::add(QString key, float value)
{
    data.push_back(Pair{key, QString::number(value)});
}

QString DataRow::get(QString key)
{
    for (Pair elem : data) {
        if (elem.key.toLower() == key.toLower())
            return elem.value;
    }
    return "";
}
