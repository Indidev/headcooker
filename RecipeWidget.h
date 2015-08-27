#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "Recipe.h"

#include <QWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include "FlowLayout.h"
#include <QFile>

#include <iostream>
#include <fstream>
using namespace std;

namespace Ui {
class RecipeWidget;
}

class RecipeWidget : public QWidget
{
    Q_OBJECT

public:
    RecipeWidget(QString id, QWidget *parent = 0);
    ~RecipeWidget();

    Recipe *getRecipe();

private:
    Ui::RecipeWidget *ui;
    Recipe *recipe;
};

#endif // RECIPEWIDGET_H
