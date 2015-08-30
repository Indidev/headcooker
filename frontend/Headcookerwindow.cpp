#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    curWidget = new RecipeChooser(this);
    ui->centralWidget->layout()->addWidget(curWidget);

    testDB();

    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}

void HeadcookerWindow::testDB() {
}

void HeadcookerWindow::moveWindow(int x, int y) {
    QRect geom = this->geometry();
    this->setGeometry(geom.x() + x, geom.y() + y, geom.width(), geom.height());
};

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
