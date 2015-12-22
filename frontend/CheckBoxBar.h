#ifndef CHECKBOXBAR_H
#define CHECKBOXBAR_H

#include <QWidget>
#include <QList>
#include <QStringList>
#include <QPushButton>
#include <QSignalMapper>
#include <QHBoxLayout>
#include "backend/Options.h"

#include <iostream>

namespace Ui {
class CheckBoxBar;
}

class CheckBoxBar : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxBar(QStringList options, QWidget *parent = 0);
    ~CheckBoxBar();

private:
    Ui::CheckBoxBar *ui;
    QStringList options;
    int curIndex;
    QList<QPushButton *> buttons;
    QSignalMapper buttonMapper;
    QLayout *layout;

private slots:
    void clicked(int id);

signals:
    void optionChanged(QString option);
    void optionChanged(int index);
protected:
    void redraw();
};

#endif // CHECKBOXBAR_H
