#pragma once
#include <QLabel>
#include <QFont>

class QLabelStyled : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelStyled(const QString& text = "", QWidget* parent = nullptr);
};
