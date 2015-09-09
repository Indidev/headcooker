#ifndef STYLEMENU_H
#define STYLEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QScrollBar>

#include "../../backend/Options.h"

namespace Ui {
class StyleMenu;
}

class StyleMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StyleMenu(QWidget *parent = 0);
    ~StyleMenu();

public slots:
    void updateStylesheet();
private:
    Ui::StyleMenu *ui;
};

#endif // STYLEMENU_H
