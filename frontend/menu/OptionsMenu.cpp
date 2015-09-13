#include "OptionsMenu.h"
#include "ui_OptionsMenu.h"

OptionsMenu::OptionsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMenu)
{
    ui->setupUi(this);

    MenuWidget *tmpTab = new StyleMenu(this);
    newLayout(ui->styleTab)->addWidget(tmpTab);
    tabs.push_back(tmpTab);

    newLayout(ui->importTab)->addWidget(new ImportMenu);

    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

OptionsMenu::~OptionsMenu()
{
    delete ui;
}

QLayout* OptionsMenu::newLayout(QWidget * widget) {
    if (widget->layout())
        delete widget->layout();
    widget->setLayout(new QGridLayout);
    return widget->layout();
}

void OptionsMenu::accept() {
    for (MenuWidget *tab : tabs)
        tab->saveChanges();

    QDialog::accept();
}

void OptionsMenu::reject() {
    QDialog::reject();
}
