#include "ExtendedLineEdit.h"

ExtendedLineEdit::ExtendedLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

ExtendedLineEdit::ExtendedLineEdit(const QString &text, QWidget *parent) : QLineEdit(text, parent)
{
}

void ExtendedLineEdit::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Backspace) {
        emit backSpacePressed();
    }

    if (event->key() == Qt::Key_Escape) {
        emit escPressed();
    }

    QLineEdit::keyPressEvent(event);
}
