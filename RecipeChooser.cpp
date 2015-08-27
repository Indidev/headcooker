#include "RecipeChooser.h"
#include "ui_RecipeChooser.h"

RecipeChooser::RecipeChooser(HeadcookerWindow *hw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeChooser)
{
    this->hw = hw;
    ui->setupUi(this);

    connect(&buttonToIDMapper, SIGNAL(mapped(QString)), hw, SLOT(clickedID(QString)));

    updateList();

    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(addRecipe()));
}

RecipeChooser::~RecipeChooser()
{
    delete ui;
}

void RecipeChooser::addRecipe() {
    QString input = ui->input->text();

    QStringList items = input.split("/");

    for (QString item : items) {
        bool ok;
        item.toLong(&ok);
        if (ok) {
            Recipe tmpR(item); //auto-save if outside of scope
            break;
        }
    }
    ui->input->setText("");
    updateList();
}

void RecipeChooser::updateList() {
    for (QPushButton * w: ui->scrollArea->findChildren<QPushButton*>()) {
        w->hide();
        delete w;
    }
    //ui->itemLayout
    QList<DataRow> rows;
    if (Database::DB().listOfRecipes(rows)) {
        for (DataRow row : rows) {
            QPushButton *item = new QPushButton(row.get("title"));
            ui->itemLayout->addWidget(item);

            buttonToIDMapper.setMapping(item, row.get("id"));
            QObject::connect(item, SIGNAL(clicked()), &buttonToIDMapper, SLOT(map()));
        }
    }
}
