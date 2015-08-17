#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}
