#include "Headcookerwindow.h"
#include "ui_Headcookerwindow.h"

HeadcookerWindow::HeadcookerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeadcookerWindow)
{
    ui->setupUi(this);

    Curler curler;



    QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/1235651228459595");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/814121185712740");
    //QString xml = curler.getQString("http://api.chefkoch.de/v2/recipes/197551083658477");

    ui->centralWidget->layout()->addWidget(new RecipeWidget(RecipeApiParser::parseRecipe(xml)));
}

HeadcookerWindow::~HeadcookerWindow()
{
    delete ui;
}
