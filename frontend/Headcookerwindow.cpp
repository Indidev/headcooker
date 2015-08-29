#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    QString id("2138001343651445");
    id = "424521133318549";
    id = "1235651228459595";

    //RecipeWidget *rw = new RecipeWidget(id);
    //ui->centralWidget->layout()->addWidget(rw);
    curWidget = new RecipeChooser(this);
    ui->centralWidget->layout()->addWidget(curWidget);

    testDB();
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}

void HeadcookerWindow::testDB() {
}

void HeadcookerWindow::clickedID(QString id) {
    showRecipe(id.toInt());
}

void HeadcookerWindow::clear() {
    curWidget->setVisible(false);
    ui->centralWidget->layout()->removeWidget(curWidget);
    curWidget->deleteLater();
}

void HeadcookerWindow::showRecipe(int id) {
    setWidget(new RecipeWidget(id, this));
}

void HeadcookerWindow::showRecipeChooser() {
    setWidget(new RecipeChooser(this));
}

void HeadcookerWindow::setWidget(QWidget * widget) {
    clear();
    curWidget = widget;
    ui->centralWidget->layout()->addWidget(curWidget);
}
