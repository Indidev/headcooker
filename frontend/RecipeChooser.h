#ifndef RECIPECHOOSER_H
#define RECIPECHOOSER_H

#include <QWidget>
#include <QSignalMapper>
#include <QLabel>
#include <QPushButton>

#include "../backend/database/Database.h"
#include "../backend/database/DataRow.h"
#include "Headcookerwindow.h"
#include <iostream>

namespace Ui {
class RecipeChooser;
}

class HeadcookerWindow;

class RecipeChooser : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeChooser(HeadcookerWindow *hw, QWidget *parent = 0);
    explicit RecipeChooser(HeadcookerWindow *hw, QString filter, QWidget *parent = 0);
    ~RecipeChooser();
    void updateList();

public slots:
    void addRecipe();
    void setFilter();
protected:
    void init(HeadcookerWindow *hw);
    QString filter;
    Ui::RecipeChooser *ui;
    HeadcookerWindow *hw;

    QSignalMapper buttonToIDMapper;
};

#endif // RECIPECHOOSER_H
