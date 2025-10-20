#include "stdafx.h"
#include "QPushButtonStyled.h"

QPushButtonStyled::QPushButtonStyled(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    // font family, size, and weight
    QFont font("Courier New", 11, QFont::Bold);
    this->setFont(font);

    this->setCursor(Qt::PointingHandCursor);
}
