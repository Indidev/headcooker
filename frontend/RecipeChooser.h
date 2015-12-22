#ifndef RECIPECHOOSER_H
#define RECIPECHOOSER_H

#include <QWidget>
#include <QSignalMapper>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QImage>
#include <QMap>
#include <QPoint>
#include <QMenu>
#include <QCursor>

#include "backend/database/Database.h"
#include "backend/database/DataRow.h"
#include "backend/Util.h"
#include "frontend/MultiTagInput.h"
#include "frontend/CheckBoxBar.h"
#include "ExtendedButton.h"
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
    explicit RecipeChooser(HeadcookerWindow *win, QWidget *parent = 0, QString filter = "");
    ~RecipeChooser();

public slots:
    void addRecipe();
    void setFilter();
    void hoverButton(QString id);
    void updateList();
    void updateStylesheet();
    void rightClickRecipe(QString id);
    void chooseRecipe(QString id);
    void changedFilterType(QString type);

protected:
    void init(HeadcookerWindow *win);
    QStringList filter;
    MultiTagInput *filterInput;
    QString curPreviewImg;

    QString curMaskPath;
    QImage maskImage;

    Ui::RecipeChooser *ui;
    HeadcookerWindow *win;

    QSignalMapper buttonToIDMapper;
    QSignalMapper previewMapper;
    QSignalMapper rightClickMapper;

    QMap<QString, QImage> previewPictures;
    QMap<QString, float> ratings;
    QColor ratingColor;
    QColor ratingBackground;
    QString ratingMask;
    bool andFilter;
};

#endif // RECIPECHOOSER_H
