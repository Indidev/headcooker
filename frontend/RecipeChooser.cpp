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

    QString style = Options::style("recipeChooser");

    if (!style.isEmpty()) {
        this->setStyleSheet(style);
    }

    connect(&buttonToIDMapper, SIGNAL(mapped(QString)), hw, SLOT(clickedID(QString)));
    connect(&previewMapper, SIGNAL(mapped(QString)), this, SLOT(hoverButton(QString)));

    updateList();

    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(addRecipe()));
    connect(ui->filterEdit, SIGNAL(returnPressed()), this, SLOT(setFilter()));

    ui->filterEdit->setObjectName("inputArea");
    ui->input->setObjectName("inputArea");
    ui->scrollArea->setObjectName("scrollArea");
    ui->scrollArea->verticalScrollBar()->setObjectName("scrollbar");

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
            item->setObjectName("recipeItem");

            ui->itemLayout->addWidget(item);
            QString id = row.get("id");

            buttonToIDMapper.setMapping(item, id);
            QObject::connect(item, SIGNAL(leftClicked()), &buttonToIDMapper, SLOT(map()));

            QPixmap previewImg(420, 280);
            previewImg.load(row.get("img_path"));
            QBitmap mask(420, 280);
            mask.load("img/image_mask.png", "png");
            previewImg.setMask(mask);

            previewPictures[id] = previewImg.scaledToWidth(210);
            previewMapper.setMapping(item, id);
            QObject::connect(item, SIGNAL(hover()), &previewMapper, SLOT(map()));

        }
    }
}

void RecipeChooser::hoverButton(QString id) {
    if (previewPictures.contains(id)) {
        if (curPreviewImg != id) {
            ui->previewImage->setPixmap(previewPictures[id]);
            curPreviewImg = id;
        }
    }
}
