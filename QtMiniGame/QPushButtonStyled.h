#pragma once
#include <QPushButton>

class QPushButtonStyled : public QPushButton
{
	Q_OBJECT

public:
	explicit QPushButtonStyled(const QString& text = "", QWidget* parent = nullptr);


};