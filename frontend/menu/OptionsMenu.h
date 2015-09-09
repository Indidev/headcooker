#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QDialog>
#include <QList>

#include "StyleMenu.h"

namespace Ui {
class OptionsMenu;
}

class OptionsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsMenu(QWidget *parent = 0);
    ~OptionsMenu();

    void setWidget(QWidget *widget);
public slots:
    void accept();
    void reject();
private:
    Ui::OptionsMenu *ui;

    QList<MenuWidget *> tabs;
    QLayout *newLayout(QWidget *widget);
};

#endif // OPTIONSMENU_H
