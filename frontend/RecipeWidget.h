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
#include <QLineEdit>
#include <QFile>
#include <QTimer>
#include <QString>
#include <QCursor>
#include <QScrollBar>
#include <QSignalMapper>

#include <iostream>
#include <fstream>

#include "ExtendedButton.h"
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

public slots:
    void displayTagInput();
    void addNewTag();
    void rightClick(QString tag);
    void leftClick(QString tag);
protected:
    Ui::RecipeWidget *ui;
    Recipe *recipe;

    FlowLayout *tagLayout;
    QPushButton *addTagButton;
    QLineEdit *addTagInput;
    QSignalMapper leftClickMapper;
    QSignalMapper rightClickMapper;

    void addTag(QString tagname);

    void init(HeadcookerWindow *win);
    void addAddTagButton();
};

#endif // RECIPEWIDGET_H
