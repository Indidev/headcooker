#ifndef RECIPECHOOSER_H
#define RECIPECHOOSER_H

#include <QWidget>
#include <QSignalMapper>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QBitmap>
#include <QMap>
#include <QPoint>
#include <QMenu>
#include <QCursor>

#include "../backend/database/Database.h"
#include "../backend/database/DataRow.h"
#include "../backend/Util.h"
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
    explicit RecipeChooser(HeadcookerWindow *hw, QWidget *parent = 0);
    explicit RecipeChooser(HeadcookerWindow *hw, QString filter, QWidget *parent = 0);
    ~RecipeChooser();

public slots:
    void addRecipe();
    void setFilter();
    void hoverButton(QString id);
    void updateList();
    void updateStylesheet();
    void rightClickRecipe(QString id);
protected:
    void init(HeadcookerWindow *hw);
    QString filter;
    QString curPreviewImg;

    QString curMaskPath;
    QImage maskImage;

    Ui::RecipeChooser *ui;
    HeadcookerWindow *hw;

    QSignalMapper buttonToIDMapper;
    QSignalMapper previewMapper;
    QSignalMapper rightClickMapper;

    QMap<QString, QImage> previewPictures;
};

#endif // RECIPECHOOSER_H
