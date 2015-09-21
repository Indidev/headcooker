#ifndef STYLEMENU_H
#define STYLEMENU_H

#include <QPushButton>
#include <QScrollBar>
#include <QPixmap>
#include <QBitmap>

#include "MenuWidget.h"
#include <QWidget>
#include "backend/Options.h"
#include "backend/Util.h"

namespace Ui {
class StyleMenu;
}

class StyleMenu : public MenuWidget
{
    Q_OBJECT
public:
    StyleMenu(QWidget *parent = 0);
    ~StyleMenu();
    void saveChanges();

public slots:
    void updateStylesheet();
private:
    Ui::StyleMenu *ui;
    QImage image;
};

#endif // STYLEMENU_H
