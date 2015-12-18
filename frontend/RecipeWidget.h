#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include "../backend/Recipe.h"
#include "../backend/Options.h"
#include "../backend/Util.h"

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
#include <QMenu>

#include <iostream>
#include <fstream>

#include "ExtendedButton.h"
#include "ExtendedLineEdit.h"
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
    void cancelAddTag();
    void updateStylesheet();
    void updateIngredients(QString servings);

    void back();
protected:
    Ui::RecipeWidget *ui;
    Recipe *recipe;
    HeadcookerWindow *win;

    QList<QPushButton*> tags;
    QList<QGroupBox*> ingredientBoxes;

    FlowLayout *tagLayout;
    QPushButton *addTagButton;
    ExtendedLineEdit *addTagInput;
    QSignalMapper leftClickMapper;
    QSignalMapper rightClickMapper;

    void addTag(QString tagname);

    void init(HeadcookerWindow *win);
    void addAddTagButton();
    void deleteTag(QString tag);

    void updateIngredients(float servings = 0.f);

};

#endif // RECIPEWIDGET_H
