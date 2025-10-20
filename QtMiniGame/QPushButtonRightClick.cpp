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
		//int wid = width() * 90 /100;
		//static QIcon red_flag(":/QtMiniGame/icon_1_red_flag.ico");
		//static QIcon question_mark(":/QtMiniGame/icon_2_question_mark.ico");
		//static bool is_red_flag = false;

		//if (icon().isNull()) 
		//{
		//	setIcon(red_flag);
		//	setIconSize(QSize(wid, wid));
		//	is_red_flag = true;
		//}
		//else 
		//{
		//	if (is_red_flag)
		//	{
		//		setIcon(question_mark);
		//		setIconSize(QSize(wid, wid));
		//		is_red_flag = !is_red_flag;
		//	}
		//	else
		//	{
		//		setIcon(QIcon());  // delete icon
		//	}
		//}

		if (rect().contains(e->pos()))
			emit clickedRight();
		e->accept();
	}
	//else if (e->button() == Qt::LeftButton)
	//{
	//	// disable button on left click
	//	if (!icon().isNull())
	//	{
	//		setIcon(QIcon());  // delete icon
	//	}
	//	setEnabled(false);
	//	

	//	// still emit the default clicked() signal
	//	QPushButton::mousePressEvent(e);
	//}
	else
		QPushButton::mousePressEvent(e);
}

void QPushButtonRightClick::mouseDoubleClickEvent(QMouseEvent* e)
{
	return;
}
