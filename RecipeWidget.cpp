#include "RecipeWidget.h"
#include "ui_RecipeWidget.h"

RecipeWidget::RecipeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    ui->setupUi(this);
}

RecipeWidget::RecipeWidget(XMLTree xmlData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeWidget)
{
    ui->setupUi(this);

    ui->recipeName->setText(xmlData.getChild("title").getValue());
    ui->subtitle->setText(xmlData.getChild("subtitle").getValue());
    ui->instructions->setText(xmlData.getChild("instructions").getValue());
}

RecipeWidget::~RecipeWidget()
{
    delete ui;
}
