#include "stdafx.h"
#include "QLabelStyled.h"

QLabelStyled::QLabelStyled(const QString& text, QWidget* parent)
    : QLabel(text, parent)
{
    QFont font("Courier New", 11, QFont::Bold);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
}
