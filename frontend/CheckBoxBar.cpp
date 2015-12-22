#include "CheckBoxBar.h"
#include "ui_CheckBoxBar.h"

CheckBoxBar::CheckBoxBar(QStringList options, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckBoxBar)
{
    ui->setupUi(this);
    curIndex = 0;
    this->options = options;

    layout = new QHBoxLayout();
    layout->setSpacing(0);
    this->setLayout(layout);

    this->setStyleSheet(Options::style("checkBoxBar"));

    connect(&buttonMapper, SIGNAL(mapped(int)), SLOT(clicked(int)));
    redraw();
}

CheckBoxBar::~CheckBoxBar()
{
    delete ui;
}

void CheckBoxBar::clicked(int id)
{
    curIndex = id;
    redraw();
    emit optionChanged(options[id]);
    emit optionChanged(id);
}

void CheckBoxBar::redraw() {

    for (QPushButton* btn : buttons) {
        layout->removeWidget(btn);
        btn->setVisible(false);
        btn->deleteLater();
    }
    buttons.clear();

    for (int i = 0; i < options.size(); i++) {
        QString styleName = "checkBoxBar_";

        if (i == 0)
                styleName += "left";
        else if (i == options.size() - 1)
                styleName += "right";
        else
                styleName += "center";

        if (curIndex == i) {
            styleName += "_active";
        }

        QPushButton *btn = new QPushButton(options[i]);
        btn->setObjectName(styleName);
        buttonMapper.setMapping(btn, i);
        connect(btn, SIGNAL(clicked()), &buttonMapper, SLOT(map()));
        buttons.append(btn);
        layout->addWidget(btn);
    }
}
