#include "stdafx.h"
#include "QPushButtonRightClick.h"


QPushButtonRightClick::QPushButtonRightClick(QWidget* parent) :
	QPushButton(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void QPushButtonRightClick::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{

		if (rect().contains(e->pos()))
			emit clickedRight();
		e->accept();
	}
	else
		QPushButton::mousePressEvent(e);
}

void QPushButtonRightClick::mouseDoubleClickEvent(QMouseEvent* e)
{
	return;
}
