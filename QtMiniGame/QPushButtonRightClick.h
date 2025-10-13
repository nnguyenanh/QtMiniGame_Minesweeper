#pragma once

#include <QPushButton>
#include <QMouseEvent>

class QPushButtonRightClick : public QPushButton
{
	Q_OBJECT

public:
	explicit QPushButtonRightClick(QWidget* parent = nullptr);

private slots:
	void mousePressEvent(QMouseEvent* e) override;

signals:
	void clickRight();

};