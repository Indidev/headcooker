#ifndef RECIPEWIDGET_H
#define RECIPEWIDGET_H

#include <QWidget>

namespace Ui {
class RecipeWidget;
}

class RecipeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeWidget(QWidget *parent = 0);
    ~RecipeWidget();

private:
    Ui::RecipeWidget *ui;
};

#endif // RECIPEWIDGET_H
