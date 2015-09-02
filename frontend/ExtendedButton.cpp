#include "ExtendedButton.h"

ExtendedButton::ExtendedButton(QWidget *parent) : QPushButton(parent)
{
    this->setMouseTracking(true);
}

ExtendedButton::ExtendedButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    this->setMouseTracking(true);
}

void ExtendedButton::mousePressEvent(QMouseEvent *event)
{
    //TODO extend this, should also consider mouse release
    emit clicked();
    if (event->button() == Qt::RightButton)
        emit rightClicked();
    else if (event->button() == Qt::LeftButton)
        emit leftClicked();
    else if (event->button() == Qt::MiddleButton)
        emit middleClicked();
}

void ExtendedButton::mouseMoveEvent(QMouseEvent *event)
{
    emit hover();
}
