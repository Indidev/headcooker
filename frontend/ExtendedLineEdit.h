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

protected:
    void backspace();

public slots:

private slots:
    void keyPressEvent(QKeyEvent *event);

signals:
    void escPressed();
    void backSpacePressed();
};

#endif // EXTENDEDLINEEDIT_H
