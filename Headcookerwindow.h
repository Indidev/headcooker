#ifndef HEADCOOKERWINDOW_H
#define HEADCOOKERWINDOW_H

#include <QMainWindow>
#include <RecipeWidget.h>
#include "Recipe.h"

namespace Ui {
class HeadcookerWindow;
}

class HeadcookerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeadcookerWindow(QWidget *parent = 0);
    ~HeadcookerWindow();

private:
    Ui::HeadcookerWindow *ui;
};

#endif // HEADCOOKERWINDOW_H
