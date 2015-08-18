#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include <QWidget>
#include "xml/XMLTree.h"

namespace Ui {
class RecipeWidget;
}

class RecipeWidget : public QWidget
{
    Q_OBJECT

public:
    RecipeWidget(QWidget *parent = 0);
    RecipeWidget(XMLTree xmlData, QWidget *parent = 0);
    ~RecipeWidget();

private:
    Ui::RecipeWidget *ui;
};

#endif // RECIPEWIDGET_H
