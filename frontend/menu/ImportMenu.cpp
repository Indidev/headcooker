#include "ImportMenu.h"
#include "ui_ImportMenu.h"

ImportMenu::ImportMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportMenu)
{
    ui->setupUi(this);

    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->inputPath, SIGNAL(textChanged(QString)), this, SLOT(inputChanged()));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui->inputPath, SIGNAL(returnPressed()), this, SLOT(open()));
    connect(ui->selectAll, SIGNAL(clicked()), this, SLOT(checkAll()));
    connect(ui->selectNone, SIGNAL(clicked()), this, SLOT(checkNone()));
    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(import()));
}

ImportMenu::~ImportMenu()
{
    delete ui;
}

void ImportMenu::openDialog()
{
    QFileDialog dialog;

    ui->inputPath->setText(dialog.getOpenFileName());
}

void ImportMenu::inputChanged() {

    bool exist = QFile::exists(ui->inputPath->text());
    ui->openButton->setEnabled(exist);

    ui->inputPath->setStyleSheet(exist?"color:black;":"color: red;");
}

void ImportMenu::open() {
    //remove all
    for (Line &line : lines) {
        ui->itemLayout->removeWidget(line.widget);
        line.widget->setVisible(false);
        line.widget->deleteLater();
    }

    lines.clear();

    QList<QString> ids;
    if (ui->firefox->isChecked())
        ids = FirefoxParser::parse(ui->inputPath->text());

    for (QString id : ids) {
        if (!Database::DB().hasRecipe(id)) {
            QWidget *w = new QWidget;
            QCheckBox *cb = new QCheckBox(w);
            cb->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            QLabel *lbl = new QLabel(Recipe(id, true).getTitle(), w);

            lines.append(Line{id, w, cb});

            w->setStyleSheet("background-color: rgba(255, 255, 255, 150); border-radius: 5;");

            w->setLayout(new QHBoxLayout);
            w->layout()->addWidget(cb);
            w->layout()->addWidget(lbl);
            w->layout()->setContentsMargins(0, 0, 0, 0);

            cb->setChecked(true);
            connect(cb, SIGNAL(stateChanged(int)), this, SLOT(checkImport()));
            ui->itemLayout->addWidget(w);
        }
    }

    checkImport();
}

void ImportMenu::checkAll() {
    for (Line &line : lines)
        line.checkbox->setChecked(true);

    if (lines.size() > 0)
        ui->importButton->setEnabled(true);
}

void ImportMenu::checkNone() {
    for (Line &line : lines)
        line.checkbox->setChecked(false);

    ui->importButton->setEnabled(false);
}

void ImportMenu::checkImport() {
    for (Line &line : lines) {
        if (line.checkbox->isChecked()) {
            ui->importButton->setEnabled(true);
            return;
        }
    }
    ui->importButton->setEnabled(false);
}

void ImportMenu::import() {
    for (int i = 0; i  <lines.size(); i++) {
        Line &line = lines[i];
        if (line.checkbox->isChecked()) {

            Recipe tmpR(line.id);
            tmpR.save();

            ui->itemLayout->removeWidget(line.widget);
            line.widget->setVisible(false);
            line.widget->deleteLater();
            lines.removeAt(i);
            i--;
        }
    }

    Options::up();
}
