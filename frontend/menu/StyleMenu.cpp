#include "StyleMenu.h"
#include "ui_StyleMenu.h"

StyleMenu::StyleMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleMenu)
{
    ui->setupUi(this);

    for (int i = 0; i < 10; i++) {
        QPushButton *item = new QPushButton("rezept");
        item->setObjectName("recipeItem");
        ui->itemLayout->addWidget(item);
    }

    //set ObjectNames
    ui->filterInput->setObjectName("inputArea");
    ui->recipeID_Input->setObjectName("inputArea");
    ui->recipeArea->setObjectName("scrollArea");
    ui->recipeArea->verticalScrollBar()->setObjectName("scrollbar");

    ui->instructions->setObjectName("instructions");
    ui->instructions->verticalScrollBar()->setObjectName("scrollbar");
    ui->backButton->setObjectName("backButton");
    ui->tag1->setObjectName("tag");
    ui->tag2->setObjectName("tag");
    ui->addTagButton->setObjectName("addTag");
    ui->tagEdit->setObjectName("tagEdit");

    //set Style box
    ui->styleBox->addItems(Options::styles());
    ui->styleBox->setCurrentText(Options::getCurStyle());
    connect(ui->styleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStylesheet()));

    updateStylesheet();
}

StyleMenu::~StyleMenu()
{
    delete ui;
}

void StyleMenu::updateStylesheet() {
    ui->chooserBox->setStyleSheet(Options::style("recipeChooser", ui->styleBox->currentText()));
    ui->recipeBox->setStyleSheet(Options::style("recipe", ui->styleBox->currentText()));
}
