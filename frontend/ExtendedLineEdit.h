#ifndef EXTENDEDLINEEDIT_H
#define EXTENDEDLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class ExtendedLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    ExtendedLineEdit(QWidget *parent = 0);
    ExtendedLineEdit(const QString &text, QWidget *parent = 0);

signals:

public slots:

private slots:
    void keyPressEvent(QKeyEvent *event);

signals:
    void escPressed();
};

#endif // EXTENDEDLINEEDIT_H
