#include "DataRow.h"

DataRow::DataRow()
{
}

void DataRow::add(QString key, QString value)
{
    data.push_back(Pair{key, value});
}

QString DataRow::get(QString key)
{
    for (Pair elem : data) {
        if (elem.key.toLower() == key.toLower())
            return elem.value;
    }
    return "";
}
