#ifndef HEADCOOKERWINDOW_H
#define HEADCOOKERWINDOW_H

#include <QMainWindow>
#include "RecipeWidget.h"
#include <sqlite3.h>

#include "Recipe.h"
#include "database/Database.h"
#include "RecipeChooser.h"

#include <unordered_map>

namespace Ui {
class HeadcookerWindow;
}

class RecipeChooser;

class HeadcookerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeadcookerWindow(QWidget *parent = 0);
    ~HeadcookerWindow();

    void showRecipe(int id);
public slots:
    void clickedID(QString id);
    void showRecipeChooser();
protected:
    void testDB();
    void clear();
    void setWidget(QWidget *widget);
private:
    Ui::HeadcookerWindow *ui;

    QWidget *curWidget;
};

#endif // HEADCOOKERWINDOW_H
