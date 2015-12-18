#ifndef HEADCOOKERWINDOW_H
#define HEADCOOKERWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "RecipeWidget.h"
#include <sqlite3.h>

#include "backend/Recipe.h"
#include "backend/database/Database.h"
#include "menu/OptionsMenu.h"
#include "RecipeChooser.h"
#include "backend/FirefoxParser.h"

#include <unordered_map>

#include <iostream>

using std::cout;
using std::endl;

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
    void moveWindow(int x, int y);
    void menuAction(QAction *action);
    void showWidget(QWidget *widget);
protected:
    void test();

private:
    Ui::HeadcookerWindow *ui;

    QWidget *curWidget;
};

#endif // HEADCOOKERWINDOW_H
