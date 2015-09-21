#include "StyleMenu.h"
#include "ui_StyleMenu.h"

StyleMenu::StyleMenu(QWidget *parent) :
    MenuWidget(parent),
    ui(new Ui::StyleMenu)
{
    ui->setupUi(this);

    for (int i = 0; i < 10; i++) {
        QPushButton *item = new QPushButton("rezept");
        item->setObjectName("recipeItem");
        ui->itemLayout->addWidget(item);
    }

    image = QImage(105, 70, QImage::Format_RGBA8888);
    image.load("img/styleMenuPreviewImage.jpg");

    //set ObjectNames
    ui->chooserBody->setObjectName("body");
    ui->filterInput->setObjectName("inputArea");
    ui->recipeID_Input->setObjectName("inputArea");
    ui->recipeArea->setObjectName("scrollArea");
    ui->recipeArea->verticalScrollBar()->setObjectName("scrollbar");
    ui->c_label1->setObjectName("text");
    ui->c_label2->setObjectName("text");

    ui->recipeBody->setObjectName("body");
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

void StyleMenu::saveChanges()
{
    Options::setCurStyle(ui->styleBox->currentText());
}

void StyleMenu::updateStylesheet() {
    QString chooserStyle = Options::style("recipeChooser", ui->styleBox->currentText());
    QString recipeStyle = Options::style("recipe", ui->styleBox->currentText());

    int cm = Util::extractCSSTag_I(chooserStyle, "body", "margin");
    int rm = Util::extractCSSTag_I(recipeStyle, "body", "margin");

    QString cMask = Util::extractCSSTag_S(chooserStyle, "image", "mask");
    QString rMask = Util::extractCSSTag_S(recipeStyle, "image", "mask");

    QImage tmpImg(image);
    QImage mask(105, 70, QImage::Format_RGBA8888);
    if (!cMask.isEmpty() && QFile::exists(cMask)) {
        mask.load(cMask);
        tmpImg.setAlphaChannel(mask.scaled(105, 70));
    }
    ui->chooserImage->setPixmap(QPixmap::fromImage(tmpImg));

    tmpImg = QImage(image);
    if (!rMask.isEmpty() && QFile::exists(rMask)) {
        mask.load(rMask);
        tmpImg.setAlphaChannel(mask.scaled(105, 70));
    }
    ui->recipeImage->setPixmap(QPixmap::fromImage(tmpImg));

    ui->chooserBox->setContentsMargins(cm, cm, cm, cm);
    ui->recipeBox->setContentsMargins(rm, rm, rm, rm);

    ui->chooserBox->setStyleSheet(chooserStyle);
    ui->recipeBox->setStyleSheet(recipeStyle);

    ui->recipeID_Input->setStyleSheet(chooserStyle);
    for (QPushButton * w: ui->recipeArea->findChildren<QPushButton*>())
        w->setStyleSheet(chooserStyle);


}
