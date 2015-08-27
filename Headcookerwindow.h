#ifndef HEADCOOKERWINDOW_H
#define HEADCOOKERWINDOW_H

#include <QMainWindow>
#include "RecipeWidget.h"
#include <sqlite3.h>

#include "Recipe.h"
#include "database/Database.h"
#include <unordered_map>

namespace Ui {
class HeadcookerWindow;
}

class HeadcookerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeadcookerWindow(QWidget *parent = 0);
    ~HeadcookerWindow();

protected:
    void testDB();
private:
    Ui::HeadcookerWindow *ui;
};

#endif // HEADCOOKERWINDOW_H
