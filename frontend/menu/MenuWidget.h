#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

class MenuWidget : public QWidget {

    Q_OBJECT
public:

    MenuWidget(QWidget * parent = 0) : QWidget(parent) {}
    virtual void saveChanges() = 0;
};

#endif // MENUWIDGET_H
