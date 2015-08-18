#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "xml/XMLTree.h"

#include <QWidget>
#include <QGroupBox>
#include <QTableWidget>

#include <iostream>
using namespace std;

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
