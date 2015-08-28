#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QList>

class DataTypes
{
public:
    struct Ingredient {
        float amount;
        QString unit;
        QString name;
        QString usageInfo;
    };

    struct IngredientList {
        QString header;
        QList<Ingredient> ingredients;
        void append(Ingredient ingredient) { ingredients.append(ingredient); }
        void append(QList<Ingredient> ingredient) { ingredients.append(ingredient); }
    };

    struct IngredientGroups {
        QList<IngredientList> groups;

        void add(QString header, Ingredient ingredient) {
            for (IngredientList &il : groups) {
                if (il.header == header) {
                    il.append(ingredient);
                    return;
                }
            }
            groups.append(IngredientList{header});
            groups.last().append(ingredient);
        }
        void add(QString header, QList<Ingredient> ingredient) {
            for (IngredientList &il : groups) {
                if (il.header == header) {
                    il.append(ingredient);
                    return;
                }
            }
            groups.append(IngredientList{header});
            groups.last().append(ingredient);
        }
    };

private:
    DataTypes();
};

#endif // DATATYPES_H
