#include "OptionsMenu.h"
#include "ui_OptionsMenu.h"

OptionsMenu::OptionsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMenu)
{
    ui->setupUi(this);
}

OptionsMenu::~OptionsMenu()
{
    delete ui;
}

void OptionsMenu::setWidget(QWidget *widget) {
    ui->centralLayout->addWidget(widget);
}
