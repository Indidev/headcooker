#ifndef MULTITAGINPUT_H
#define MULTITAGINPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include "frontend/ExtendedLineEdit.h"


namespace Ui {
class MultiTagInput;
}

class MultiTagInput : public QWidget
{
    Q_OBJECT

public:
    explicit MultiTagInput(QWidget *parent = 0);
    ~MultiTagInput();
    QStringList getTags();
    void setTag(QString tag);
    void setTags(QStringList tags);

    void focus();
private:
    Ui::MultiTagInput *ui;
    ExtendedLineEdit *input;
    QStringList tags;
    QList<QWidget *> tagWidgets;
    QSignalMapper tagmapper;

    void refresh();
    void changed();

private slots:
    void addTag();
    void removeTag(QString tag);
    void backSpacePressed();

signals:
    void tagsChanged();
};

#endif // MULTITAGINPUT_H
