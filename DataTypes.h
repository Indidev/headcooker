#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>

class DataTypes
{
public:
    struct Ingredient {
        float amount;
        QString unit;
        QString name;
        QString usageInfo;
    };

private:
    DataTypes();
};

#endif // DATATYPES_H
