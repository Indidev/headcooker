#include "RecipeChooser.h"
#include "ui_RecipeChooser.h"

RecipeChooser::RecipeChooser(HeadcookerWindow *hw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeChooser)
{
    init(hw);
}

RecipeChooser::RecipeChooser(HeadcookerWindow *hw, QString filter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeChooser)
{
    this->filter = filter;
    init(hw);
    ui->filterEdit->setText(filter);
}

void RecipeChooser::init(HeadcookerWindow *hw)
{
    this->hw = hw;
    ui->setupUi(this);

    connect(&buttonToIDMapper, SIGNAL(mapped(QString)), hw, SLOT(clickedID(QString)));
    connect(&previewMapper, SIGNAL(mapped(QString)), this, SLOT(hoverButton(QString)));
    connect(&rightClickMapper, SIGNAL(mapped(QString)), this, SLOT(rightClickRecipe(QString)));

    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(addRecipe()));
    connect(ui->filterEdit, SIGNAL(returnPressed()), this, SLOT(setFilter()));

    connect(Options::ptr(), SIGNAL(updated()), this, SLOT(updateList()));

    ui->bodyWidget->setObjectName("body");
    ui->label->setObjectName("text");
    ui->label_2->setObjectName("text");
    ui->filterEdit->setObjectName("inputArea");
    ui->input->setObjectName("inputArea");
    ui->scrollArea->setObjectName("scrollArea");
    ui->scrollArea->verticalScrollBar()->setObjectName("scrollbar");
    ui->previewImage->setObjectName("image");

    updateList();
}

RecipeChooser::~RecipeChooser()
{
    delete ui;
}

void RecipeChooser::addRecipe() {
    QString input = ui->input->text();
    QRegExp regex("\\D+");

    QStringList items = input.split(regex, QString::SkipEmptyParts);

    for (QString item : items) {
        bool ok;
        item.toLong(&ok);
        if (ok) {
            Recipe tmpR(item);
            tmpR.save();
            break;
        }
    }
    ui->input->setText("");
    updateList();
}

void RecipeChooser::setFilter() {
    filter = ui->filterEdit->text();
    updateList();
}

void RecipeChooser::updateList() {
    for (QPushButton * w: ui->scrollArea->findChildren<QPushButton*>()) {
        ui->itemLayout->removeWidget(w);
        w->setVisible(false);
        w->deleteLater();
    }
    previewPictures.clear();

    //ui->itemLayout
    QList<DataRow> rows;
    bool success = filter.isEmpty()
            ?Database::DB().listOfRecipes(rows)
            :Database::DB().recipesContaining(filter, rows);
    if (success) {
        for (DataRow row : rows) {
            ExtendedButton *item = new ExtendedButton(row.get("title"));
            item->setAutoFillBackground(true);
            item->setObjectName("recipeItem");

            ui->itemLayout->addWidget(item);
            QString id = row.get("id");

            buttonToIDMapper.setMapping(item, id);
            QObject::connect(item, SIGNAL(leftClicked()), &buttonToIDMapper, SLOT(map()));

            rightClickMapper.setMapping(item, id);
            QObject::connect(item, SIGNAL(rightClicked()), &rightClickMapper, SLOT(map()));

            QImage previewImg(420, 280, QImage::Format_RGBA8888);
            previewImg.load(row.get("img_path"));

            previewPictures[id] = previewImg.scaled(210, 140);
            ratings[id] = row.get("rating").toFloat();
            previewMapper.setMapping(item, id);
            QObject::connect(item, SIGNAL(hover()), &previewMapper, SLOT(map()));

        }
    }
    updateStylesheet();
}

void RecipeChooser::hoverButton(QString id) {
    if (previewPictures.contains(id)) {
        if (curPreviewImg != id) {
            QImage tmpImage(previewPictures[id]);
            if (!curMaskPath.isEmpty())
                tmpImage.setAlphaChannel(maskImage);
            ui->previewImage->setPixmap(QPixmap::fromImage(tmpImage));
            curPreviewImg = id;

            ui->ratingLbl->setPixmap(QPixmap::fromImage(Util::getRatingImg(ratings[id], ratingMask, ratingColor, ratingBackground)));
        }
    }
}

void RecipeChooser::updateStylesheet() {

    QString style = Options::style("recipeChooser");
    curMaskPath = Util::extractCSSTag_S(style, "image", "mask");

    if (QFile::exists(curMaskPath)) {
        maskImage.load(curMaskPath);
        maskImage = maskImage.scaled(210, 140);
    } else
        curMaskPath = "";
    int m = Util::extractCSSTag_I(style, "body", "margin");

    setContentsMargins(m, m, m, m);

    //rating
    ratingColor = Util::extractCSSTag_C(style, "rating", "color");
    ratingBackground = Util::extractCSSTag_C(style, "rating", "background");
    ratingMask = Util::extractCSSTag_S(style, "rating", "mask");

    this->setStyleSheet(style);
    ui->input->setStyleSheet(style);
    for (QPushButton * w: ui->scrollArea->findChildren<QPushButton*>())
        w->setStyleSheet(style);
}

void RecipeChooser::rightClickRecipe(QString id) {
    QMenu menu;

    menu.addAction("delete");

    QAction * action = menu.exec(QCursor::pos());

    if (action) {
        if (action->toolTip() == "delete") {
            Database::DB().deleteRecipe(id.toInt());

            updateList();
        }
    }
}
