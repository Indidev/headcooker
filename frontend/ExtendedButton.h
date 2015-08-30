#ifndef EXTENDEDBUTTON_H
#define EXTENDEDBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QMouseEvent>

class ExtendedButton : public QPushButton
{
    Q_OBJECT
public:
    ExtendedButton(QWidget *parent = 0);
    ExtendedButton(QString &text, QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *event);

signals:
    void leftClicked();
    void rightClicked();
};

#endif // EXTENDEDBUTTON_H
