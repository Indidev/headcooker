#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "xml/XMLTree.h"
#include "Curler.h"
#include "RecipeApiParser.h"

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
    RecipeWidget(QWidget *parent = 0);
    RecipeWidget(XMLTree xmlData, QWidget *parent = 0);
    ~RecipeWidget();

private:
    Ui::RecipeWidget *ui;

    QPixmap fetchImage(XMLTree &xmlData);
};

#endif // RECIPEWIDGET_H
