#include "ExtendedButton.h"

ExtendedButton::ExtendedButton(QWidget *parent) : QPushButton(parent)
{
}

ExtendedButton::ExtendedButton(QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

void ExtendedButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit rightClicked();
    else if (event->button() == Qt::LeftButton)
        emit leftClicked();
}
