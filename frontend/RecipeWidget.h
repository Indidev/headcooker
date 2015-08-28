#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "../backend/Recipe.h"
#include "FlowLayout.h"
#include "Headcookerwindow.h"

#include <QWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QFile>

#include <iostream>
#include <fstream>
using namespace std;

namespace Ui {
class RecipeWidget;
}

class HeadcookerWindow;

class RecipeWidget : public QWidget
{
    Q_OBJECT

public:
    RecipeWidget(QString id, HeadcookerWindow *win, QWidget *parent = 0);
    RecipeWidget(int id, HeadcookerWindow *win, QWidget *parent = 0);
    RecipeWidget(Recipe &recipe, HeadcookerWindow *win, QWidget *parent = 0);
    ~RecipeWidget();
    Recipe *getRecipe();

protected:
    Ui::RecipeWidget *ui;
    Recipe *recipe;

    void init(HeadcookerWindow *win);
};

#endif // RECIPEWIDGET_H
