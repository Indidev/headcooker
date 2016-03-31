#include "MultiTagInput.h"
#include "ui_MultiTagInput.h"

#include <iostream>

MultiTagInput::MultiTagInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiTagInput)
{
    ui->setupUi(this);
    ui->outerWidget->setObjectName("inputArea");
    input = NULL;

    connect(&tagmapper, SIGNAL(mapped(QString)), this, SLOT(removeTag(QString)));

    refresh();
}

MultiTagInput::~MultiTagInput()
{
    delete ui;
}

void MultiTagInput::setTag(QString tag) {
    if (tag.trimmed() != "" && !tags.contains(tag, Qt::CaseInsensitive)) {
        tags.append(tag);
        refresh();
    }
}

void MultiTagInput::setTags(QStringList tags) {
    for (QString tag : tags) {
        setTag(tag);
    }
}

void MultiTagInput::addTag() {
    QString tag = input->text();

    if (tag.trimmed() != "" && !tags.contains(tag, Qt::CaseInsensitive)) {
        tags.append(tag);
        refresh();
        input->setFocus();
    }
    changed();
}

void MultiTagInput::removeTag(QString tag) {
        tags.removeAll(tag);
        QString tmp = input->text();
        int cursorPos = input->cursorPosition();
        refresh();
        changed();
        input->setText(tmp);
        input->setCursorPosition(cursorPos);
}

void MultiTagInput::backSpacePressed() {
    if (input->cursorPosition() == 0 && !tags.empty()) {
        removeTag(tags.last());
    }
}

void MultiTagInput::refresh() {

    //remove old input
    if (input != NULL) {
        ui->contentArea->layout()->removeWidget(input);
        input->setVisible(false);
        input->deleteLater();
    }

    //remove tags
    for (QWidget *w : tagWidgets) {
        ui->contentArea->layout()->removeWidget(w);
        w->setVisible(false);
        w->deleteLater();
    }
    tagWidgets.clear();

    //add tags
    for (QString tag : tags) {
        QWidget* w = new QWidget();

        w->setLayout(new QHBoxLayout());

        w->layout()->setContentsMargins(5, 0, 0, 0);


        QLabel *tagL = new QLabel(tag);
        w->layout()->addWidget(tagL);

        QPushButton *tagB = new QPushButton("  x  ");
        w->layout()->addWidget(tagB);

        tagmapper.setMapping(tagB, tag);
        connect(tagB, SIGNAL(clicked()), &tagmapper, SLOT(map()));

        w->setObjectName("filterTag");
        tagL->setObjectName("filterTag_text");
        tagB->setObjectName("filterTag_button");

        ui->contentArea->addWidget(w);
        tagWidgets.append(w);
    }

    //add input
    input = new ExtendedLineEdit();
    input->setObjectName("inputArea");
    input->setStyleSheet("border: none; background-color: rgba(0, 0, 0, 0); margin:1;");
    connect(input, SIGNAL(returnPressed()), this, SLOT(addTag()));
    connect(input, SIGNAL(backSpacePressed()), this, SLOT(backSpacePressed()));
    ui->contentArea->addWidget(input);
}

QStringList MultiTagInput::getTags()
{
    return tags;
}

void MultiTagInput::changed() {
    input->setFocus();
    emit tagsChanged();
}

void MultiTagInput::focus() {
    input->setFocus();
}
