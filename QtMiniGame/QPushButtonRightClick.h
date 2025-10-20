#pragma once

#include <QPushButton>
#include <QMouseEvent>

class QPushButtonRightClick : public QPushButton
{
	Q_OBJECT

public:
	explicit QPushButtonRightClick(QWidget* parent = nullptr);

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseDoubleClickEvent(QMouseEvent* e);

signals:
	void clickedRight();

};