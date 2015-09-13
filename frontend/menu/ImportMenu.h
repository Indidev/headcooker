#ifndef IMPORTMENU_H
#define IMPORTMENU_H

#include <QWidget>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include "backend/FirefoxParser.h"
#include "backend/Recipe.h"
#include "backend/Options.h"

#include <iostream>

using namespace std;

namespace Ui {
class ImportMenu;
}

class ImportMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ImportMenu(QWidget *parent = 0);
    ~ImportMenu();

public slots:
    void openDialog();

    void inputChanged();
    void open();
    void checkNone();
    void checkAll();
    void checkImport();
    void import();

private:
    Ui::ImportMenu *ui;

    struct Line {
        QString id;
        QWidget* widget;
        QCheckBox *checkbox;
    };

    QList<Line> lines;
};

#endif // IMPORTMENU_H
