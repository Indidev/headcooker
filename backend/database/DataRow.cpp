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

 QString DataRow::get(const QString key)
{
    for (Pair elem : data) {
        if (elem.key.toLower() == key.toLower())
            return elem.value;
    }
    return "";
}

bool DataRow::operator==(const DataRow &rhs)
{
    bool equal = true;

    if (this->data.size() != rhs.data.size()) {
        return false;
    }

    for (Pair p : this->data) {
        for (Pair elem : rhs.data) {
            if (elem.key.toLower() == p.key.toLower())
                if (p.value != elem.value) {
                    equal = false;
                }

            if (!equal)
                break;

        }
    }

    return equal;
}
