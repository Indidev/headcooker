#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);



    QString xml = Curler::get("http://api.chefkoch.de/v2/recipes/1235651228459595");

    ui->centralWidget->layout()->addWidget(new RecipeWidget(RecipeApiParser::parseRecipe(xml)));
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}
