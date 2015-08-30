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
    connect(ui->filterEdit, SIGNAL(returnPressed()), this, SLOT(setFilter()));
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
    cout << filter.toStdString() << endl;
    updateList();
}

void RecipeChooser::updateList() {
    for (QPushButton * w: ui->scrollArea->findChildren<QPushButton*>()) {
        ui->itemLayout->removeWidget(w);
        w->setVisible(false);
        w->deleteLater();
    }
    //ui->itemLayout
    QList<DataRow> rows;
    bool success = filter.isEmpty()
            ?Database::DB().listOfRecipes(rows)
            :Database::DB().recipesContaining(filter, rows);
    if (success) {
        for (DataRow row : rows) {
            QPushButton *item = new QPushButton(row.get("title"));
            ui->itemLayout->addWidget(item);

            buttonToIDMapper.setMapping(item, row.get("id"));
            QObject::connect(item, SIGNAL(clicked()), &buttonToIDMapper, SLOT(map()));
        }
    }
}
